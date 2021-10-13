#pragma once
#include<iostream>
#include<string>

class Fraction
{
private:
	int numerator;
	unsigned int denominator;

	void reduce_fraction();

public:
	Fraction(int numerator = 0, unsigned int denominator = 1);

	int get_numerator() const;
	int get_denominator() const;

	static int gcd(int, int);

	friend std::ostream& operator<<(std::ostream&, const Fraction&);
	friend std::istream& operator>>(std::istream&, Fraction&);
};