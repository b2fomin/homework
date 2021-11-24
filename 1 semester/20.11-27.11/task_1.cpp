#include<iostream>

template<std::size_t N>
struct factorial
{
	static constexpr std::size_t value = N * factorial<N - 1>::value;
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

template<std::size_t N, std::size_t K>
struct bin_coeff
{
	static constexpr std::size_t value = factorial<N>::value / factorial<N - K>::value / factorial<K>::value;
};

int main()
{
	std::cout << bin_coeff<10, 4>::value;
	return 0;
}