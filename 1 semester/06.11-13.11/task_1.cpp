#include<iostream>

template<typename... Args>
auto size1(Args...)
{
	std::size_t result = 0;
	(result += ... += sizeof(Args));
	return result;
}

std::size_t size2()
{
	return 0;
}

template<typename First, typename... Args>
auto size2(First first, Args... args)
{
	return sizeof(first) + size2(args...);
}

int main()
{
	std::cout << size1(5, 4, "123")<<std::endl;
	std::cout << size2(5, 4, "123");
	return 0;
}