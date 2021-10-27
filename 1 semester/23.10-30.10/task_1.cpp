#include<iostream>
#include<vector>

enum class Errors
{
	STRING_ERROR,
	INT_ERROR
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
	std::vector<std::pair<std::string, Errors>>::iterator it;
	for (it=exception_array.begin();it<exception_array.end();++it)
	{
		if (it->first != "foo") continue;
		if(it->second==Errors::INT_ERROR) std::cout << "Negative number";
		exception_array.erase(it);
		break;
	}

	return 0;
}