#include<iostream>

enum class Months
{
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

int days_in_month(Months month)
{
	switch (month)
	{
	case Months::JANUARY:
		return 31;
		break;
	case Months::FEBRUARY:
		return 28;
		break;
	case Months::MARCH:
		return 31;
		break;
	case Months::APRIL:
		return 30;
		break;
	case Months::MAY:
		return 31;
		break;
	case Months::JUNE:
		return 30;
		break;
	case Months::JULY:
		return 31;
		break;
	case Months::AUGUST:
		return 31;
		break;
	case Months::SEPTEMBER:
		return 30;
		break;
	case Months::OCTOBER:
		return 31;
		break;
	case Months::NOVEMBER:
		return 30;
		break;
	case Months::DECEMBER:
		return 31;
		break;
	}
}

int main()
{
	std::cout << days_in_month(Months::JANUARY);
	return 0;
}