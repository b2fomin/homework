#include<iostream>
#include<algorithm>
#include<regex>

int main()
{
	std::string data = "sezauffugufeu-2369@yopmail1.com, quodduddovouga-4935@yop!mail2.com    queixeihogupe-1926yopmail3.com fuhaubroddunei-1618@yopmail4com 12345 hello world wissucrubipa-1685@yopmail5.com";
	std::regex pattern(R"((\w*)@(\w*\.\w*))");
	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern, { 2 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));
}