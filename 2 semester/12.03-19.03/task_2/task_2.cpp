#include<iostream>
#include<boost/locale.hpp>
#include<locale>
#include"Translation.hpp"

int main()
{
	system("chcp 1251");
	boost::locale::generator generator;
	std::locale sys_locale = generator(boost::locale::util::get_system_locale());

	std::string string;
	std::cin.imbue(sys_locale);
	std::cin >> string;

	string = boost::locale::conv::to_utf<char>(string, sys_locale);
	auto string2=boost::locale::conv::utf_to_utf<char32_t>(string);

	Translator::translate_from_rus_into_en(string2);

	string=boost::locale::conv::utf_to_utf<char>(string2);
	string = boost::locale::conv::from_utf<char>(string, sys_locale);
	std::cout << string;

	return 0;
}