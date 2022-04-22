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