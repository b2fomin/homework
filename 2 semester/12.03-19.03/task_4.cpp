#include<iostream>
#include<algorithm>
#include<vector>
#include<regex>

int main()
{
	std::vector<int> days_in_month{31,28,31,30,31,30,31,31,30,31,30,31};
	std::string data = "2015.12.03 23:15:15";
	std::regex pattern1(R"((\d{4})\.(\d{2})\.(\d{2}))");
	std::regex pattern2(R"((\d{2}):(\d{2}):(\d{2}))");

	std::cout << "Date:" << std::endl;

	std::for_each(std::sregex_iterator(data.cbegin(), data.cend(), pattern1), std::sregex_iterator(), [&days_in_month](const std::smatch& m)
		{
			int year = std::stoi(m[1]);
			int month = std::stoi(m[2]);
			int day = std::stoi(m[3]);
			if (month <= 12 && ((month == 2 && day == 29 && !year % 4) || day <= days_in_month[month-1]))
				std::cout << m[0] << std::endl;
		});

	std::cout << std::endl << "Time:" << std::endl;

	std::for_each(std::sregex_iterator(data.cbegin(), data.cend(), pattern2), std::sregex_iterator(), [](const std::smatch& m)
		{
			int hours = std::stoi(m[1]);
			int minutes = std::stoi(m[2]);
			int seconds = std::stoi(m[3]);
			if (hours < 24 && minutes < 60 && seconds < 60)
				std::cout << m[0] << std::endl;
		});

	return 0;
}