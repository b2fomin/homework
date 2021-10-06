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