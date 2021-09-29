#include<iostream>

struct Time
{
	unsigned int year;
	unsigned int month : 4;
	unsigned int day : 5;
	unsigned int hours : 5;
	unsigned int minutes : 6;
	unsigned int seconds : 6;
	unsigned int milliseconds : 10;
};

std::ostream& operator<<(std::ostream& out, const Time& time)
{
	return out << time.year << " " << time.month << " " << time.day << " " << time.hours  << " " << time.minutes << " " << time.seconds << " " << time.milliseconds;
}

int main()
{
	Time now{ 2021,10,30,14,25,30,500 };
	std::cout << now;
	return 0;
}