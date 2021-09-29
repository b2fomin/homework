#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

struct Date
{
	int year;
	int month;
	int day;

	Date(int year,int month,int day)
	{
		this->year = year;
		this->month = month;
		this->day = day;
	}

	void print()
	{
		cout << setw(2) << day << '.' << setw(2) << setfill('0') << month << '.' << year % 100;
	}
};

int main()
{
	Date today{ 795,9,29 };
	today.print();
	return 0;
}