#include "Fraction.hpp"

namespace frac
{
	Fraction::Fraction(int numerator, unsigned int denominator) :numerator(numerator), denominator(denominator)
	{
		reduce_fraction();
	};

	int Fraction::gcd(int number_1, int number_2)
	{
		if (number_2 == 0) return number_1;
		else return gcd(number_2, number_1 % number_2);
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

	int Fraction::get_numerator() const { return numerator; };
	int Fraction::get_denominator() const { return denominator; };

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

		int dividend = Fraction::lcm(left.denominator, right.denominator);
		new_fraction.denominator = static_cast<unsigned int>(dividend);
		new_fraction.numerator = left.numerator * dividend / left.denominator +
			right.numerator * dividend / right.denominator;

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

	Fraction operator-(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		int dividend = Fraction::lcm(left.denominator, right.denominator);
		new_fraction.denominator = static_cast<unsigned int>(dividend);
		new_fraction.numerator = left.numerator * dividend / left.denominator -
			right.numerator * dividend / right.denominator;

		new_fraction.reduce_fraction();
		return new_fraction;
	}

	Fraction operator/(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		new_fraction.numerator = left.numerator * right.denominator;
		new_fraction.denominator = left.denominator * right.numerator;

		new_fraction.reduce_fraction();
		return new_fraction;
	}

	bool operator==(const Fraction& left, const Fraction& right)
	{
		return(left.numerator == right.numerator) && (left.denominator == right.denominator);
	}

	bool operator<(const Fraction& left, const Fraction& right)
	{
		int divident = Fraction::lcm(left.denominator, right.denominator);
		return (left.numerator * divident / left.denominator < right.numerator* divident / right.denominator);
	}

	bool operator>(const Fraction& left, const Fraction& right)
	{
		int divident = Fraction::lcm(left.denominator, right.denominator);
		return (left.numerator * divident / left.denominator > right.numerator * divident / right.denominator);
	}

	bool operator<=(const Fraction& left, const Fraction& right)
	{
		int divident = Fraction::lcm(left.denominator, right.denominator);
		return (left.numerator * divident / left.denominator <= right.numerator * divident / right.denominator);
	}

	bool operator>=(const Fraction& left, const Fraction& right)
	{
		int divident = Fraction::lcm(left.denominator, right.denominator);
		return (left.numerator * divident / left.denominator >= right.numerator * divident / right.denominator);
	}

	Fraction Fraction::operator+=(const Fraction& other)
	{
		return operator+(*this, other);
	}

	Fraction Fraction::operator*=(const Fraction& other)
	{
		return operator*(*this, other);
	}

	Fraction Fraction::operator-=(const Fraction& other)
	{
		return operator-(*this, other);
	}

	Fraction Fraction::operator/=(const Fraction& other)
	{
		return operator/(*this, other);
	}

	Fraction Fraction::operator++()
	{
		numerator += denominator;
		return *this;
	}

	Fraction Fraction::operator--()
	{
		numerator -= denominator;
		return *this;
	}

	Fraction Fraction::operator++(int)
	{
		Fraction old_fraction{ numerator,denominator };
		numerator += denominator;
		return old_fraction;
	}

	Fraction Fraction::operator--(int)
	{
		Fraction old_fraction{ numerator,denominator };
		numerator -= denominator;
		return old_fraction;
	}

	Fraction::operator double()
	{
		return (double)numerator / denominator;
	}
}