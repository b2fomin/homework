#include "Fraction.hpp"

Fraction::Fraction(int numerator, unsigned int denominator) :numerator(numerator), denominator(denominator) {};

int Fraction::gcd(int number_1, int number_2)
{
	int old_number_1 = number_1;
	int old_number_2 = number_2;
	while (number_1 != number_2)
	{
		(number_1 > number_2) ? number_1 -= number_2 : number_2 -= number_1;
	}

	return old_number_1 * old_number_2 / number_1;
}

void Fraction::reduce_fraction()
{
	int divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
}