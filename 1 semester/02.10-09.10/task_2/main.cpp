#include "Temperature.hpp"
#include<iostream>

int main()
{
	Temperature temp = Temperature(0);
	std::cout << temp.get_value(Temperature::coefficients.Kelvin)<<std::endl;
	temp.set_value(0, Temperature::coefficients.Fahrenheit);
}