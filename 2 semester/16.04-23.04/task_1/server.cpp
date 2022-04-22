#include"server.h"

Server::Server(std::size_t port, std::filesystem::path path)
	: ioc{}, ctx{ ssl::context::sslv23_server }, acceptor{ ioc, tcp::endpoint(net::ip::address_v4::any(), port) }, path{ path }
{
	ctx.set_options(
		boost::asio::ssl::context::default_workarounds
		| boost::asio::ssl::context::no_sslv2
		| boost::asio::ssl::context::single_dh_use);
	ctx.set_password_callback(std::bind(&Server::get_password, this));
	ctx.use_certificate_chain_file((path / "rootca.crt").string());
	ctx.use_private_key_file((path / "rootca.key").string(), boost::asio::ssl::context::pem);
	ctx.use_tmp_dh_file((path / "dh2048.pem").string());
};

std::string Server::get_password()
{
	return "j37e!#LLE84HFzVx";
}

Server::~Server() { stop(); };

bool Server::start()
{
	try
	{
		wait_connection();
		thr_context = std::thread([this] {ioc.run(); });
	}
	catch (std::exception& ex)
	{
		std::cout << "Server::start: " << ex.what() << std::endl;
		return false;
	}
	std::cout << "Server started successfully" << std::endl;
	return true;
}
void Server::wait_connection()
{
	auto stream = std::make_shared<ssl::stream<tcp::socket>>(ioc, ctx);
	acceptor.async_accept(stream->lowest_layer(), [this, stream](err_code ec)
		{
			if (ec) fail(ec, "Server::wait_connection");
			else
			{
				std::cout << stream->lowest_layer().remote_endpoint() << " connected" << std::endl;

				auto newconn = std::make_shared<Connection>(Connection::owner::server, ioc, ctx,
					std::move(*stream), messages_in);
				clients.emplace(0, "", newconn, 0);
				newconn->connect_to_client();
				send_to_client(std::move(newconn), ServerCommand::Message, "Welcome!");
				wait_connection();
			}
		});
}
void Server::stop()
{
	ioc.stop();
	if (thr_context.joinable()) thr_context.join();
}

void Server::send_to_client(std::shared_ptr<Connection> client, const Message& msg)
{
	if (client && client->is_connected())
	{
		client->send(msg);
	}
	else
	{
		std::cout << client->remote_endpoint() << "has been disconnected" << std::endl;
		client.reset();
		clients.erase(client);
	}
}

void Server::send_to_all_clients(const Message& msg, std::shared_ptr<Connection> client_to_ignore = nullptr)
{
	for (auto& struct_client : clients)
	{
		auto client = struct_client.connection;
		if (client && client->is_connected())
		{
			if (client != client_to_ignore)
			{
				client->send(msg);
			}
		}
		else
		{
			std::cout << client->remote_endpoint() << "has been disconnected" << std::endl;
			client.reset();
			clients.erase(client);
		}
	}
}

void Server::Update(bool wait = false)
{
	if (wait) messages_in.wait();
	while (!messages_in.empty())
	{
		proceed_received_message(messages_in.front());
		messages_in.pop();
	}
}

void Server::proceed_received_message(const Message msg)
{
	auto json_msg = msg.msg;
	auto cmd = static_cast<ClientCommand>(std::stoi(json_msg.get<std::string>("command")));
	switch (cmd)
	{
	case ClientCommand::Message:
	{
		auto client = clients.find(msg.connection);
		if (client->connection && client->chat_partner_id)
		{
			send_to_client(clients.get<2>().find(client->chat_partner_id)->connection,
				ServerCommand::Message, msg.msg.get<std::string>("argument1"));
			send_to_client(msg.connection, ServerCommand::NoMessage);
		}
		else send_to_client(msg.connection, ServerCommand::Message, "You're not chatting with anyone");
	}
	return;
	case ClientCommand::LogIn:
	{
		if (msg.msg.size() != 4)
		{
			send_to_client(msg.connection, ServerCommand::Message, "Invalid number of arguments");
			return;
		}
		pt::ptree root; pt::read_json((path / "passwords.json").string(), root);

		for (pt::ptree::value_type& branch : root)
		{
			auto user = branch.second;
			if (user.get<std::string>("login") == json_msg.get<std::string>("argument1") &&
				user.get<std::string>("password") == json_msg.get<std::string>("argument2"))
			{
				if (clients.get<2>().count(std::stoi(user.get<std::string>("id"))))
				{
					send_to_client(msg.connection, ServerCommand::Message, "This user is already authorized");
					return;
				}

				for (auto iter = clients.begin(); iter != clients.end(); ++iter)
				{
					if (iter->connection == msg.connection)
					{
						clients.modify(iter, [&user](Client& client)
							{
								client.nickname = user.get<std::string>("nickname");
								client.id = std::stoi(user.get<std::string>("id"));
							});
					}
				}
				send_to_client(msg.connection, ServerCommand::Message, "Authorization's successful");
				return;
			}
		}
		send_to_client(msg.connection, ServerCommand::Message, "Invalid login or password");
	}
	return;
	case ClientCommand::Register:
	{
		if (msg.msg.size() != 5)
		{
			send_to_client(msg.connection, ServerCommand::Message, "Invalid number of arguments");
			return;
		}
		pt::ptree root; pt::read_json((path / "passwords.json").string(), root);
		pt::ptree user;
		std::string nickname = msg.msg.get<std::string>("argument3");
		int id = root.size() + 1;

		user.add("login", msg.msg.get<std::string>("argument1"));
		user.add("password", msg.msg.get<std::string>("argument2"));
		user.add("nickname", nickname);
		user.put("id", id);

		for (auto& regis_users : root)
			if (regis_users.second.get<std::string>("login") == user.get<std::string>("login"))
			{
				send_to_client(msg.connection, ServerCommand::Message, "This account already exists");
				return;
			}

		root.add_child(std::to_string(id), user);
		for (auto iter = clients.begin(); iter != clients.end(); ++iter)
		{
			if (iter->connection == msg.connection)
			{
				clients.modify(iter, [&nickname, &id](Client& client)
					{
						client.nickname = nickname;
						client.id = id;
					});
			}
		}
		pt::write_json((path / "passwords.json").string(), root);
		send_to_client(msg.connection, ServerCommand::Message, "Registarion's successful");
	}
	return;
	case ClientCommand::Chat:
	{
		auto command = msg.msg.get<std::string>("argument1");
		if ((command == "begin" && msg.msg.size() != 5) || (command == "end" && msg.msg.size() != 3))
		{
			send_to_client(msg.connection, ServerCommand::Message, "Invalid number of arguments");
			return;
		}
		auto client = clients.find(msg.connection);
		if (command == "end")
		{
			for (auto iter = clients.begin(); iter != clients.end(); ++iter)
			{
				if (iter->id == client->id)
				{
					clients.modify(client, [](Client& client) {client.chat_partner_id = 0; });
					clients.modify(iter, [](Client& another_client) {another_client.chat_partner_id = 0; });
				}
			}
			return;
		}
		else if (command == "begin")
		{
			if (client->nickname == "")
			{
				send_to_client(msg.connection, ServerCommand::Message, "You're not authorized yet.");
				return;
			}
			if (client->chat_partner_id)
			{
				send_to_client(msg.connection, ServerCommand::Message, "You're already chatting with someone");
				return;
			}
			if (!clients.get<2>().find(client->chat_partner_id)->chat_partner_id)
			{
				send_to_client(msg.connection, ServerCommand::Message, "User's already chatting with someone");
				return;
			}
			std::string chat_partner_nickname;
			int chat_partner_id;
			if (msg.msg.get<std::string>("argument2") == "nickname")
			{
				chat_partner_nickname = msg.msg.get<std::string>("argument3");

				if (!clients.get<1>().count(chat_partner_nickname))
				{
					send_to_client(msg.connection, ServerCommand::Message, "User not found");
					return;
				}
				else chat_partner_id = clients.get<1>().find(chat_partner_nickname)->id;

			}
			else if (msg.msg.get<std::string>("argument2") == "id")
			{
				chat_partner_id = std::stoi(msg.msg.get<std::string>("argument3"));
				chat_partner_nickname = clients.get<1>().find(chat_partner_nickname)->nickname;
			}
			else
			{
				send_to_client(msg.connection, ServerCommand::Message, "Invalid argument");
				return;
			}

			if (clients.get<2>().count(chat_partner_id) < clients.get<1>().count(chat_partner_nickname))
			{
				send_to_client(msg.connection, ServerCommand::Message, "Nickname is not unique. Try to find via id");
				return;
			}

			for (auto iter = clients.begin(); iter != clients.end(); ++iter)
			{
				if (chat_partner_id == iter->id)
				{
					clients.modify(iter, [&client](Client& another_client)
						{another_client.chat_partner_id = client->id; });
				}
				else if (iter->id == client->id)
				{
					clients.modify(client, [&chat_partner_id](Client& client) {client.chat_partner_id = chat_partner_id; });
				}
			}
			auto chat_partner = clients.get<2>().find(client->chat_partner_id);
			send_to_client(chat_partner->connection, ServerCommand::Message, "You're now chatting with " + client->nickname);
			send_to_client(msg.connection, ServerCommand::Message, "You're now chatting with " + chat_partner->nickname);
			return;

		}
		else
		{
			send_to_client(msg.connection, ServerCommand::Message, "Invalid argument");
			return;
		}
	}
	return;
	default:
		send_to_client(msg.connection, ServerCommand::Message, "Unknown command");
		return;
	}

}