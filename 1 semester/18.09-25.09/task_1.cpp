#include <iostream>

int fib(int number)
{
	if (number == 1 || number == 2) return 1;
	return fib(number - 1) + fib(number - 2);
}

int main()
{
	using namespace std;

	cout << "Enter number of Fibonacci sequence: ";
	int number;
	cin >> number;

	cout << endl << "Result is " << fib(number);
	
	return 0;
}