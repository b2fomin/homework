#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

struct Date
{
private: const int month_duration[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	int day;
	int month;
	int year;

	Date(int day = 0, int month = 0, int year = 0) : year(year), month(month), day(day)
	{

	}

	void print()
	{
		cout << setw(2) << day << '.' << setw(2) << setfill('0') << month << '.' << setw(2) << setfill('0') << year % 100;
	}

	Date& operator=(const Date& other)
	{
		year = other.year;
		month = other.month;
		day = other.day;
	}

	Date operator+(const Date& other)
	{
		Date new_date;
		new_date.day = day + other.day;

		int duration = month_duration[max(month, other.month)];
		new_date.month = month + other.month + new_date.day / duration;
		new_date.day %= duration;

		new_date.year = year + other.year + new_date.month / 12;
		new_date.month %= 12;
		return new_date;
	}

	bool operator==(const Date& other) { return (year == other.year && month == other.month && day == other.day); };

	bool operator<(const Date& other) { return (year < other.year || month < other.month || day < other.day); };

	bool operator>(const Date& other) { return (year > other.year || month > other.month || day > other.day); };
};

int main()
{
	Date today{ 29,9,2021 };
	Date tomorrow{ 30,9,2021 };
	Date yesterday{ 28,9,2021 };
	(today + tomorrow).print();
	cout << endl << boolalpha << (today < tomorrow) << " " << (today == today) << " " << (today < yesterday) << endl;
	return 0;
}