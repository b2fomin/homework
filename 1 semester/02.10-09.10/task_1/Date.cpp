#include "Date.hpp"



Date::Date(int year=0, int month=0, int day=0):month_duration{ 31,28,31,30,31,30,31,31,30,31,30,31 }
{
	set_year(year);
	set_month(month);
	set_day(day);
}

void Date::set_year(int year) { this->year = year; };//date may be BC
void Date::set_month(int month)
{
	if (0 < month <= 12) this->month = month;
	else throw "Invalid month number";
}
void Date::set_day(int day)
{
	if (0 < day <= month_duration[month]) this->day = day;
	else throw "Invalid day number";
}

int Date::get_day() const { return day; };
int Date::get_month() const { return month; };
int Date::get_year() const { return year; };

Date& Date::operator=(const Date& other)
{
	year = other.year;
	month = other.month;
	day = other.day;
}

Date Date::operator+(const Date& other)
{
	Date new_date;
	new_date.day = day + other.day;

	int duration = month_duration[std::max(month, other.month)];
	new_date.month = month + other.month + new_date.day / duration;
	new_date.day %= duration;

	new_date.year = year + other.year + new_date.month / 12;
	new_date.month %= 12;
	return new_date;
}

bool Date::operator==(const Date& other) { return (year == other.year && month == other.month && day == other.day); };

bool Date::operator<(const Date& other) { return (year < other.year || month < other.month || day < other.day); };

bool Date::operator>(const Date& other) { return (year > other.year || month > other.month || day > other.day); };