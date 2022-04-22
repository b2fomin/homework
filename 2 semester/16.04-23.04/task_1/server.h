#include"include_common.h"
#include"connection.h"
#include<map>
#include<boost/multi_index_container.hpp>
#include<boost/multi_index/member.hpp>
#include<boost/multi_index/hashed_index.hpp>

namespace multi = boost::multi_index;

class Server : public std::enable_shared_from_this<Server>
{
private:
	struct Client
	{
		int id;
		std::string nickname;
		std::shared_ptr<Connection> connection;
		int chat_partner_id;
	};

	using users_multi_index = multi::multi_index_container <
		Client, multi::indexed_by <
		multi::hashed_non_unique <
		multi::member < Client, std::shared_ptr<Connection>, &Client::connection > >,
		multi::hashed_non_unique <
		multi::member < Client, std::string, &Client::nickname > >,
		multi::hashed_non_unique <
		multi::member < Client, int, &Client::id > > > >;

	tsqueue<Message> messages_in;
	net::io_context ioc;
	ssl::context ctx;
	std::thread thr_context;
	tcp::acceptor acceptor;
	users_multi_index clients;
	std::filesystem::path path;
public:
	Server(std::size_t, std::filesystem::path);

private:
	std::string get_password();

public:
	~Server();

	bool start();
private:
	void wait_connection();
public:
	void stop();

	template<typename... Args>
	void send_to_client(std::shared_ptr<Connection> client, ServerCommand cmd, Args... args)
	{
		Message msg = create_msg_to_send(cmd, args...);
		send_to_client(client, msg);
	}

	void send_to_client(std::shared_ptr<Connection>, const Message&);

	template<typename... Args>
	void send_to_all_clients(ServerCommand cmd, std::shared_ptr<Connection> client_to_ignore, Args... args)
	{
		Message msg = create_msg_to_send(cmd, args...);
		send_to_all_clients(msg, client_to_ignore);
	}
	void send_to_all_clients(const Message&, std::shared_ptr<Connection> = nullptr);

	void Update(bool = false);

private:
	template<typename... Args>
	Message create_msg_to_send(ServerCommand cmd, Args... args)
	{
		std::vector<std::string> argumets{ args... };
		pt::ptree ptree;
		ptree.add("command", std::to_string(static_cast<int>(cmd)));
		for (int i = 0; i < argumets.size(); ++i) ptree.add("argument" + std::to_string(i + 1), argumets[i]);
		return Message{ nullptr, ptree };
	}

	void proceed_received_message(const Message);
};