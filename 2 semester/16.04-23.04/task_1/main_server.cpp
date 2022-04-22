#pragma once
#include "server.h"
int main()
{
	setlocale(LC_ALL, "RUS");
	Server srv(15001, std::filesystem::current_path()/"server");
	srv.start();
	while (true)
	{
		srv.Update(true);
	}
}