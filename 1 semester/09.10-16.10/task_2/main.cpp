#include<iostream>
#include"Fraction.hpp"

int main()
{
	using namespace frac;
	Fraction frac1{ 4,3 };
	Fraction frac2{ 5,6 };

	std::cout << frac1 << std::endl << frac2 << std::endl << frac1 + frac2 <<
		std::endl << frac1 * frac2 << std::endl << frac1 - frac2 << std::endl << frac1 / frac2 << std::endl << (double)frac1;
}