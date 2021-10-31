#include<iostream>
#include<vector>

enum class Errors
{
	STRING_ERROR = -1,
	INT_ERROR = -2
};

std::vector<std::pair<std::string, Errors>> exception_array{};

int foo(int number)
{
	if (number < 0)
	{
		exception_array.push_back(std::make_pair("foo", Errors::INT_ERROR));
		return number;
	}
	else
	{
		return ++number;
	}
}

int main()
{
	int number = -1;
	foo(number);
	for (auto it=exception_array.begin();it<exception_array.end();++it)
	{
		if (it->first == "foo") return (int)it->second;
	}

	return 0;
}