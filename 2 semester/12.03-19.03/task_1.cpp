#include<iostream>
#include<iomanip>
#include<locale>

int main()
{
	long double money;
	std::cin.imbue(std::locale("de_DE.UTF-8"));
	std::cout << "EUR: ";
	std::cin >> std::get_money(money, true);

	std::cout.imbue(std::locale("ru_RU.UTF-8"));
	std::cout << std::endl << "RUB: " << std::put_money(money*107.58, true);

	return 0;
}