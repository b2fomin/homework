#pragma once
#include"include_common.h"

class Connection;

struct Message
{
public:
	mutable std::shared_ptr<Connection> connection;
	pt::ptree msg;

	Message(std::shared_ptr<Connection> connection, pt::ptree msg)
		: connection{ connection }, msg{ msg }
	{
		auto time = std::chrono::current_zone()
			->to_local(std::chrono::system_clock::now());
		this->msg.put("time", std::format("{:%d-%m-%Y %H:%M:%S}", time));
	}

	Message(std::shared_ptr<Connection> connection, std::string string)
		: connection{ connection }
	{
		std::stringstream message{ string };
		std::string line;
		int i = 0;
		while (std::getline(message, line, ' '))
		{
			if (!i++)
			{
				line.erase(line.begin(), line.begin() + 2);
				msg.put("command", line);
			}
			else msg.put("argument" + std::to_string(i), line);
		}
		auto time = std::chrono::current_zone()
			->to_local(std::chrono::system_clock::now());
		msg.put("time", std::format("{:%d-%m-%Y %H:%M:%S}", time));
	}
};

