#include<iostream>
#include<boost/locale.hpp>
#include<locale>

int main()
{
	system("chcp 1251");
	boost::locale::generator generator;
	std::locale sys_locale = generator(boost::locale::util::get_system_locale());

	std::string string;
	std::cin.imbue(sys_locale);
	std::cin >> string;

	boost::locale::conv::to_utf<char>(string, sys_locale);
	boost::locale::conv::utf_to_utf<wchar_t>(string);

	return 0;
}