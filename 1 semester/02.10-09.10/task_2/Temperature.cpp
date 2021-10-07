#include"Temperature.hpp"

const temperature::Temperature::Coefficients temperature::Temperature::coefficients
{
	[](double value) { return value + 273.15; },
	[](double value) { return 1.8 * value + 32; },
	[](double value) {return 0.8 * value; }
};

void temperature::Temperature::set_value(double value, converter calculator = [](double value) {return value; })
{
	this->value = calculator(value);
	if (this->value < -273.15) throw "Invalid temperature";
}

double temperature::Temperature::get_value(converter calculator = [](double value) {return value; }) const
{
	return calculator(value);
}

temperature::Temperature::Temperature(double value)
{
	Temperature::set_value(value);
}