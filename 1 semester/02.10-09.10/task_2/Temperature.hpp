#pragma once
#include<iostream>
#include<functional>

namespace temperature
{
	using converter = std::function<double(double)>;

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
}