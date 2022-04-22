#pragma once
#pragma warning(disable:4996)
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include<boost/asio.hpp>
#include<boost/asio/ssl.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

#include<iostream>
#include"tsqueue.h"
#include<string>
#include<memory>
#include<sstream>
#include<chrono>
#include<format>
#include<vector>
#include<algorithm>
#include<filesystem>

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace ssl = net::ssl;
using err_code = boost::system::error_code;
namespace pt = boost::property_tree;

void fail(const err_code, const char*);

enum class ServerCommand
{
	Message,
	NoMessage
};

enum class ClientCommand
{
	LogIn,
	Register,
	Chat,
	Message
};

const std::string delimeter = "#";