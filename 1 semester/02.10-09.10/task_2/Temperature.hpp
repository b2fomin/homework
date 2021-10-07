#pragma once
#include<iostream>
#include<functional>

typedef std::function<double(double)> converter;

class Temperature
{
	double value;
	const struct Coefficients
	{
		converter Kelvin;
		converter Fahrenheit;
		converter Reamur;
	};
public:
	static const Coefficients coefficients;
	void set_value(double, converter);
	double get_value(converter) const;
	Temperature(double);
};