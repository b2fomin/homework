#include"Temperature.hpp"

Temperature::Coefficients Temperature::coefficients
{
	[](double value) { return value + 273.15; },
	[](double value) { return 1.8 * value + 32; },
	[](double value) {return 0.8 * value; }
};

void Temperature::set_value(double value, converter calculator = [](double value) {return value; })
{
	this->value = calculator(value);
	if (this->value < -273.15) throw "Invalid temperature";
}

double Temperature::get_value(converter calculator = [](double value) {return value; }) const
{
	return calculator(value);
}

Temperature::Temperature(double value)
{
	Temperature::set_value(value);
}