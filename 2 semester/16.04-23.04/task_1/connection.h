#include"include_common.h"
#include"message.h"

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

	void send(const Message msg);

	void connect_to_server(tcp::resolver::results_type& endpoints);

	void connect_to_client();

private:
	void handshake(ssl::stream_base::handshake_type);

	void read_message();

	void write_message();
};