#include "Date.hpp"
#include<iostream>
#include<iomanip>

int main()
{
	using namespace std;
	Date today(1,1,1);
	Date tomorrow{ 30,9,2021 };
	Date yesterday{ 28,9,2021 };
	cout << today << " " << tomorrow << endl;
	cout << (today + tomorrow);
	cout << endl << boolalpha << (today < tomorrow) << " " << (today == today) << " " << (today < yesterday) << endl;
	return 0;
}