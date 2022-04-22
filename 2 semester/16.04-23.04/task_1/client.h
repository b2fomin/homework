#include"include_common.h"
#include"Connection.h"
#include<future>

class Client
{
private:
	static std::string cmd_begin;
	net::io_context ioc;
	ssl::context ctx;
	tsqueue<Message> messages;
	std::unique_ptr<Connection> connection;
	std::thread thr_context;
	std::string message;
	std::future<void> cin_thread = std::async([this]() {std::getline(std::cin, message);
	send(create_msg_to_send(std::move(message))); });

public:
	Client(std::filesystem::path);

private:
	bool verify_certificate(bool,
		boost::asio::ssl::verify_context&);

public:
	~Client();

	void connect(const char*, std::size_t);

bool is_connected();

void disconnect();

void send(const Message);

	template<typename... Args>
	void send(ClientCommand cmd, Args... args)
	{
		Message msg = create_msg_to_send(cmd, args...);
		send(msg);
	}

	void Update(bool wait = false);

private:
	template<typename... Args>
	Message create_msg_to_send(ClientCommand cmd, Args... args)
	{
		std::vector<std::string> argumets{ args... };
		pt::ptree ptree;
		ptree.add("command", std::to_string(static_cast<int>(cmd)));
		for (int i = 0; i < argumets.size(); ++i) ptree.add("argument" + std::to_string(i + 1), argumets[i]);
		return Message{ nullptr, ptree };
	}

	Message create_msg_to_send(std::string);

	ClientCommand convert_string_to_client_command(std::string);

	void proceed_received_message(const Message);
};
