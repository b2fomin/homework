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