#include "Date.hpp"


Date::Date(int year = 1, int month = 1, int day = 1) :month_duration{ 31,28,31,30,31,30,31,31,30,31,30,31 }
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

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << std::setw(2) << date.day << '.' << std::setw(2) << std::setfill('0') << date.month << '.' << std::setw(2) << std::setfill('0');
	if (date.year < 0) out << -date.year << " BC";
	else out << date.year;
	return out;
}

std::istream& operator>>(std::istream& in, const Date& date)//input format is day.month.year
{
	std::string answer;
	in >> answer;
	int fields[3]{ date.day, date.month, date.year };

	for (auto& field : fields)
	{
		std::string current = "";
		
		for (auto& elem : answer)
		{
			if (elem != '.') current += elem;
			else
			{
				answer.erase(answer.begin() + current.size() + 1);
				break;
			}
		}

		field = std::stoi(current);
	}
	return in;
}