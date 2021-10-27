#include<iostream>
#include"Fraction.hpp"

int main()
{
	using namespace frac;
	Fraction frac1{ 4,3 };
	Fraction frac2{ 5,6 };
	Fraction frac3 = frac1;
	frac3 += frac2;

	std::cout << frac1 << std::endl << frac2 << std::endl << frac3 << std::endl << frac1 + frac2 <<
		std::endl << frac1 * frac2 << std::endl << frac1 - frac2 << std::endl << frac1 / frac2 << std::endl << (double)frac1<<std::endl;

	try
	{
		Fraction frac4{ 4,0 };
	}
	catch (const std::runtime_error& exception)
	{
		std::cout << exception.what() << std::endl;
		throw;
	}
}