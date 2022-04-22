#include"client.h"

Client::Client(std::filesystem::path path)
	:ioc{}, ctx{ ssl::context::sslv23_client }
{
	ctx.set_verify_mode(ssl::context::verify_peer);
	ctx.set_verify_callback(
		std::bind(&Client::verify_certificate, this, std::placeholders::_1, std::placeholders::_2));
	ctx.load_verify_file((path / "rootca.crt").string());
}

