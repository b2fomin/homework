#include<iostream>

template<typename Function, typename... Args>
auto call_function(Function function, Args... args)
{
	return function(args...);
}

int main()
{
	std::cout << std::boolalpha << call_function([](int n1, int n2) {return n1 < n2; }, 5, 4) << std::endl;
	return 0;
}