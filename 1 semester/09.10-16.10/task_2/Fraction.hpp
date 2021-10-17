#pragma once
#include<iostream>
#include<string>

namespace frac
{
	class Fraction
	{
	public:
		static int gcd(int, int);
		static int lcm(int, int);
	private:
		int numerator;
		unsigned int denominator;

		void reduce_fraction();

	public:
		Fraction(int numerator = 0, unsigned int denominator = 1);

		int get_numerator() const;
		int get_denominator() const;

		operator double();
		friend std::ostream& operator<<(std::ostream&, const Fraction&);
		friend std::istream& operator>>(std::istream&, Fraction&);
		friend Fraction operator+(const Fraction&, const Fraction&);
		friend Fraction operator*(const Fraction&, const Fraction&);
		friend Fraction operator-(const Fraction&, const Fraction&);
		friend Fraction operator/(const Fraction&, const Fraction&);
		Fraction& operator+=(const Fraction&);
		Fraction& operator*=(const Fraction&);
		Fraction& operator-=(const Fraction&);
		Fraction& operator/=(const Fraction&);
		Fraction operator++();
		Fraction operator--();
		Fraction operator++(int);
		Fraction operator--(int);
		friend bool operator==(const Fraction&, const Fraction&);
		friend bool operator>(const Fraction&, const Fraction&);
		friend bool operator<(const Fraction&, const Fraction&);
		friend bool operator>=(const Fraction&, const Fraction&);
		friend bool operator<=(const Fraction&, const Fraction&);
	};
}