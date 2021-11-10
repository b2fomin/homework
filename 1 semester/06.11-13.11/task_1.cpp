#include<iostream>

template<typename... Args>
auto size1(Args...)
{
	std::size_t result = 0;
	(result += ... += sizeof(Args));
	return result;
}


int main()
{
	std::cout << size1(5, 4, "123");
	return 0;
}