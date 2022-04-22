#pragma once
#include"connection.h"

Connection::Connection(owner m_owner, net::io_context& ioc, ssl::context& ctx, ssl::stream<tcp::socket>&& stream, tsqueue<Message>& messages_in)
	: ioc{ ioc }, ctx{ ctx }, stream{ std::move(stream) }, messages_in{ messages_in }, m_owner{ m_owner }
{}

Connection::~Connection() {};

std::string Connection::remote_endpoint()
{
	std::stringstream ss; ss << stream.lowest_layer().remote_endpoint();
	return ss.str();
}

bool Connection::is_connected()
{
	return stream.lowest_layer().is_open();
}

void Connection::disconnect()
{
	if (is_connected())
	{
		net::post(ioc, [this] {stream.lowest_layer().close(); });
	}
}

void Connection::send(const Message msg)
{
	net::post(ioc, [this, msg]
		{
			bool queue_is_empty = messages_out.empty();

			messages_out.push(msg);

			if (queue_is_empty) //because another messages are processing
				write_message();
		});
}

void Connection::connect_to_server(tcp::resolver::results_type& endpoints)
{
	if (m_owner == owner::client)
	{
		net::async_connect(stream.lowest_layer(), endpoints, [this](const err_code ec, tcp::endpoint)
			{
				if (ec) fail(ec, "Connection::connect_to_server");
				else handshake(ssl::stream_base::client);
			});
	}
}

void Connection::connect_to_client()
{
	if (m_owner == owner::server)
	{
		if (stream.lowest_layer().is_open()) handshake(ssl::stream_base::server);
	}
}

void Connection::handshake(ssl::stream_base::handshake_type who)
{
	err_code ec;
	stream.handshake(who, ec);		
	if (ec) fail(ec, "Connection::handshake");
	else read_message();		
}

void Connection::read_message()
{
	net::async_read_until(stream, streambuf, "}\n", [this](const err_code ec, std::size_t length)
		{
			if (ec)
			{
				fail(ec, "Connection::read_messages");
				stream.lowest_layer().close();
			}
			else
			{
				std::stringstream message; message << std::istream(&streambuf).rdbuf();
				streambuf.consume(length);

				pt::ptree msg; pt::read_json(message, msg);
				if (m_owner == owner::client) messages_in.emplace(nullptr, msg);
				else messages_in.emplace(shared_from_this(), msg);
				read_message();
			}
		});
}

void Connection::write_message()
{
	std::stringstream message; pt::write_json(message, messages_out.front().msg); std::string msg = message.str();

	net::async_write(stream, net::buffer(msg.data(), msg.size()), [this](const err_code ec, std::size_t length)
		{
			if (ec)
			{
				fail(ec, "Connection::write_message");
				stream.lowest_layer().close();
			}
			else
			{
				messages_out.pop();
				if (!messages_out.empty()) write_message();
			}
		});
}
