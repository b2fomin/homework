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