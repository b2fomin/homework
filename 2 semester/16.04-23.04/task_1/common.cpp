#include"include_common.h"

void fail(const err_code ec, const char* what)
{
	std::cout << what << ": " << ec.message() << std::endl;
}
