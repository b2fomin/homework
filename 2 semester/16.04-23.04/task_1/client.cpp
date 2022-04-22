#include"client.h"

Client::Client(std::filesystem::path path)
	:ioc{}, ctx{ ssl::context::sslv23_client }
{
	ctx.set_verify_mode(ssl::context::verify_peer);
	ctx.set_verify_callback(
		std::bind(&Client::verify_certificate, this, std::placeholders::_1, std::placeholders::_2));
	ctx.load_verify_file((path / "rootca.crt").string());
}

bool Client::verify_certificate(bool preverified,
	boost::asio::ssl::verify_context& ctx)
{
	char subject_name[256];
	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

	return preverified;
}

void Client::connect(const char* host, std::size_t port)
{
	tcp::resolver resolver{ ioc };
	auto endpoints = resolver.resolve(host, std::to_string(port));
	auto stream = ssl::stream<tcp::socket>(ioc, ctx);

	if (!SSL_set_tlsext_host_name(stream.native_handle(), host))
	{
		boost::system::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
		throw boost::system::system_error{ ec };
	}

	connection = std::make_unique<Connection>(Connection::owner::client, ioc, ctx,
		std::move(stream), messages);

	connection->connect_to_server(endpoints);

	thr_context = std::thread{ [this] {ioc.run(); } };
}

bool Client::is_connected()
{
	if (connection) return connection->is_connected();
	else return false;
}

void Client::disconnect()
{
	if (is_connected()) connection->disconnect();

	ioc.stop();
	if (thr_context.joinable()) thr_context.join();
	connection.release();
}

Client::~Client()
{
	disconnect();
}

void Client::send(const Message msg)
{
	if (is_connected()) connection->send(msg);
}

void Client::Update(bool wait = false)
{
	while (!messages.empty())
	{
		proceed_received_message(messages.front());
		messages.pop();
	}
}

Message Client::create_msg_to_send(std::string string)
{
	std::stringstream ss{ string };
	std::string word;
	std::string command;
	std::getline(ss, word, ' ');
	for (int i = 0; i < delimeter.size(); ++i)
	{
		if (word[i] != delimeter[i])
		{
			return create_msg_to_send(ClientCommand::Message, string);
		}
	}
	word.erase(word.begin(), word.begin() + delimeter.size());
	ClientCommand cmd = convert_string_to_client_command(word);
	std::vector<std::string> args;
	while (std::getline(ss, word, ' '))
	{
		args.push_back(word);
	}
	return create_msg_to_send(cmd, args);
}

ClientCommand Client::convert_string_to_client_command(std::string string)
{
	if (string == "login") return ClientCommand::LogIn;
	if (string == "register") return ClientCommand::Register;
	if (string == "chat") return ClientCommand::Chat;
	throw std::exception("Invalid command");
}

void Client::proceed_received_message(const Message msg)
{
	auto json_msg = msg.msg;
	auto cmd = static_cast<ServerCommand>(std::stoi(json_msg.get<std::string>("command")));
	switch (cmd)
	{
	case ServerCommand::Message:
	{
		std::cout << json_msg.get<std::string>("argument1") << std::endl;
	}
	case ServerCommand::NoMessage:
	{
		using namespace std::chrono_literals;

		if (cin_thread.wait_for(0ms) == std::future_status::ready)
		{
			cin_thread.get();
			cin_thread = std::async([this]() {std::getline(std::cin, message);
			send(create_msg_to_send(std::move(message))); });
		}
	}
	return;
	}
}