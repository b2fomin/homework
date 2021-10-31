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
		if (denominator == 0) throw std::runtime_error("Division by zero!");
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
				if (other.numerator != std::stoi(current)) throw std::length_error("Too large number");
				current = "";
			}
			else current += elem;
		}

		other.denominator = std::stoi(current);
		if (other.denominator != std::stoi(current)) throw std::length_error("Too large number");
		other.reduce_fraction();

		return in;
	}

	Fraction operator+(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		int dividend = 0;
		long long int current = Fraction::lcm(left.denominator, right.denominator);
		if ((int)current == current) dividend = current;
		else throw std::length_error("Too large number");
		
		new_fraction.denominator = static_cast<unsigned int>(dividend);
		current = left.numerator * dividend / left.denominator +
			right.numerator * dividend / right.denominator;
		if ((int)current == current) new_fraction.numerator = current;
		else throw std::length_error("Too large number");

		new_fraction.reduce_fraction();
		return new_fraction;
	}

	Fraction operator*(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		long long int current = left.numerator * right.numerator;
		if ((int)current == current) new_fraction.numerator = current;
		else throw std::length_error("Too large number");

		current = left.denominator * right.denominator;
		if ((unsigned int)current == current) new_fraction.denominator = current;
		else throw std::length_error("Too large number");

		new_fraction.reduce_fraction();
		return new_fraction;
	}

	Fraction operator-(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		long long int current = Fraction::lcm(left.denominator, right.denominator);
		int dividend = 0;
		if ((int)current == current) dividend = current;
		else throw std::length_error("Too large number");
		
		new_fraction.denominator = static_cast<unsigned int>(dividend);
		
		current = left.numerator * dividend / left.denominator -
			right.numerator * dividend / right.denominator;
		if ((int)current == current) new_fraction.numerator = current;
		else throw std::length_error("Too large number");

		new_fraction.reduce_fraction();
		return new_fraction;
	}

	Fraction operator/(const Fraction& left, const Fraction& right)
	{
		Fraction new_fraction;

		long long int current = left.numerator * right.denominator;
		if ((int)current == current) new_fraction.numerator = current;
		else throw std::length_error("Too large number");

		current = left.denominator * right.numerator;
		if ((unsigned int)current == current) new_fraction.denominator = current;
		else throw std::length_error("Too large number");

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

	Fraction& Fraction::operator+=(const Fraction& other)
	{
		return *this = operator+(*this, other);
	}

	Fraction& Fraction::operator*=(const Fraction& other)
	{
		return *this = operator*(*this, other);
	}

	Fraction& Fraction::operator-=(const Fraction& other)
	{
		return *this = operator-(*this, other);
	}

	Fraction& Fraction::operator/=(const Fraction& other)
	{
		return *this = operator/(*this, other);
	}

	Fraction Fraction::operator++()
	{
		long long int current = numerator + denominator;
		if ((int)current == current) numerator = current;
		else throw std::length_error("Too large number");
		return *this;
	}

	Fraction Fraction::operator--()
	{
		long long int current = numerator - denominator;
		if ((int)current == current) numerator == current;
		else throw std::length_error("Too large number");
		return *this;
	}

	Fraction Fraction::operator++(int)
	{
		Fraction old_fraction{ numerator,denominator };
		long long int current = numerator - denominator;
		if ((int)current == current) numerator == current;
		else throw std::length_error("Too large number");
		return old_fraction;
	}

	Fraction Fraction::operator--(int)
	{
		Fraction old_fraction{ numerator,denominator };
		long long int current = numerator - denominator;
		if ((int)current == current) numerator == current;
		else throw std::length_error("Too large number");
		return old_fraction;
	}

	Fraction::operator double()
	{
		return (double)numerator / denominator;
	}
}