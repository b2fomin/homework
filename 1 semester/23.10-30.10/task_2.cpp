#include<iostream>
#include<exception>

void foo(int& number)
{
	if (number < 0) throw std::invalid_argument("Negative number is prohibited");
	++number;
}

double divide(double number1, double number2)
{
	if (number2 == 0) throw std::runtime_error("Division by zero!");
	return number1 / number2;
}

int main()
{
	try
	{
		int arr[5]{ 1,2,3,4,5 };
		int number = 6;
		if (number >= 5)
		{
			throw std::out_of_range("Out of arr's range");
		}
		std::cout << arr[number];
	}
	catch (const std::out_of_range& exception)
	{
		std::cout << exception.what()<<std::endl;
	}

	try
	{
		int number = pow(10, 10);
		if (number != pow(10, 10)) throw std::length_error("Lenght error");
	}
	catch (const std::length_error& exception)
	{
		std::cout << exception.what()<<std::endl;
	}

	try
	{
		int number = -1;
		foo(number);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what()<<std::endl;
	}

	try
	{
		double result = divide(1, 0);
	}
	catch (const std::runtime_error& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	return 0;
}