#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<regex>

int main()
{
	std::fstream file("./task_1/test.txt", std::ios_base::in);

	std::string data;

	while (!file.eof())
	{
		data += file.get();
	}

	std::regex pattern(R"((/\*(([^(\*/)])*)\*/)|(//(.*)$))");

	file.close();
	file.open("./task_1/test.txt", std::ios_base::out);
	file << std::regex_replace(data, pattern, "");


	return 0;
}