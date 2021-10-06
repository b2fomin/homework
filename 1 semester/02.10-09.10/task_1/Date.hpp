#pragma once
#include<iostream>
#include<string>
#include<iomanip>

class Date
{
	const int month_duration[12];
	int day;
	int month;
	int year;

public:
	
	void set_day(int);
	void set_month(int);
	void set_year(int);

	int get_day() const;
	int get_month() const;
	int get_year() const;

	Date(int, int, int);

	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream, const Date&);
	
	Date& operator=(const Date&);
	Date operator+(const Date&);
	bool operator==(const Date&);
	bool operator<(const Date&);
	bool operator>(const Date&);

};