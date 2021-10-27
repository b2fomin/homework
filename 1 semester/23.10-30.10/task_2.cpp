#include<iostream>
#include<exception>

int main()
{
	try
	{
		int arr[5]{ 1,2,3,4,5 };
		std::cout << arr[6];
	}
	catch (const std::out_of_range& exception)
	{
		std::cout << exception.what();
	}

	try
	{
		int number = pow(10, 5);
	}
	catch (const std::length_error& exception)
	{
		std::cout << exception.what();
	}

	try
	{

	}
	catch (const std::exception&)
	{

	}

	return 0;
}