#include<iostream>
#include<iomanip>

template<std::size_t N>
struct factorial
{
	static constexpr long long unsigned int value = N * factorial<N - 1>::value;
};

template<>
struct factorial<1>
{
	static constexpr std::size_t value = 1;
};

template<>
struct factorial<0>
{
	static constexpr std::size_t value = 1;
};

template<std::size_t accuracy>
struct e
{
	static constexpr long double value = 1.0 / factorial<accuracy>::value + e<accuracy - 1>::value;
};

template<>
struct e<0>
{
	static constexpr double value = 1.0;
};

int main()
{
	std::cout << std::setprecision(20) << e<60>::value;
	return 0;
}