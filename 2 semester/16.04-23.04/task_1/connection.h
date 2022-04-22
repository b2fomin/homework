#include"include_common.h"
#include"Message.h"

class Connection :public std::enable_shared_from_this<Connection>
{
public:
	enum class owner
	{
		server,
		client
	};

private:
	tsqueue<Message>& messages_in;
	tsqueue<Message> messages_out;
	ssl::stream<tcp::socket> stream;
	net::io_context& ioc;
	ssl::context& ctx;
	owner m_owner;
	net::streambuf streambuf{ 65536 };

public:
	Connection(owner, net::io_context&, ssl::context&, ssl::stream<tcp::socket>&&, tsqueue<Message>&);

	~Connection();

	std::string remote_endpoint();

	bool is_connected();

	void disconnect();

	void send(const Message msg)
	{
		net::post(ioc, [this, msg]
			{
				bool queue_is_empty = messages_out.empty();

				messages_out.push(msg);

				if (queue_is_empty) //because another messages are processing
					write_message();
			});
	}

	void connect_to_server(tcp::resolver::results_type& endpoints)
	{
		if (m_owner == owner::client)
		{			net::async_connect(stream.lowest_layer(), endpoints, [this](const err_code ec, tcp::endpoint)
				{
					if (ec) fail(ec, "Connection::connect_to_server");
					else handshake(ssl::stream_base::client);
				});
		}
	}

	void connect_to_client()
	{
		if (m_owner == owner::server)
		{
			if (stream.lowest_layer().is_open()) handshake(ssl::stream_base::server);
		}
	}

private:
	void handshake(ssl::stream_base::handshake_type);

	void read_message();

	void write_message();
};