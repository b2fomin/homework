#include "Date.hpp"



Date::Date(int year=0, int month=0, int day=0):month_duration{ 31,28,31,30,31,30,31,31,30,31,30,31 }
{
	set_year(year);
	set_month(month);
	set_day(day);
}
