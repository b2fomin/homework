#include<iostream>

template<std::size_t N>
struct fib
{
	static constexpr std::size_t value = fib<N - 1>::value + fib<N - 2>::value;
};

template<>
struct fib<1>
{
	static constexpr std::size_t value = 1;
};

template<>
struct fib<0>
{
	static constexpr std::size_t value = 0;
};

int main()
{
	std::cout << fib<20>::value;
	return 0;
}