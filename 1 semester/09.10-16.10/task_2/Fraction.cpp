#include "Fraction.hpp"

Fraction::Fraction(int numerator, unsigned int denominator) :numerator(numerator), denominator(denominator)
{
	reduce_fraction();
};

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

int Fraction::lcm(int number_1, int number_2)
{
	return number_1 * number_2 / gcd(number_1, number_2);
}

void Fraction::reduce_fraction()
{
	int divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
}

std::ostream& operator<<(std::ostream& out, const Fraction& other)
{
	return out << other.numerator << '/' << other.denominator;
}

std::istream& operator>>(std::istream& in, Fraction& other) // input format: "numerator"/"denominator"
{
	std::string fraction;
	in >> fraction;
	std::string current = "";

	for (auto& elem : fraction)
	{
		if (elem == '/')
		{
			other.numerator = std::stoi(current);
			current = "";
		}
	}

	other.denominator = std::stoi(current);
	other.reduce_fraction();

	return in;
}

Fraction operator+(const Fraction& left, const Fraction& right)
{
	Fraction new_fraction;

	int dividend = Fraction::lcm(left.denominator,right.denominator);
	new_fraction.denominator = static_cast<unsigned int>(dividend);
	new_fraction.numerator = left.numerator * dividend / left.denominator +
							right.numerator * dividend / left.denominator;
	
	new_fraction.reduce_fraction();
	return new_fraction;
}

Fraction operator*(const Fraction& left, const Fraction& right)
{
	Fraction new_fraction;

	new_fraction.numerator = left.numerator * right.numerator;
	new_fraction.denominator = left.denominator * right.denominator;

	new_fraction.reduce_fraction();
	return new_fraction;
}