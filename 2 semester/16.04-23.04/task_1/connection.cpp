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