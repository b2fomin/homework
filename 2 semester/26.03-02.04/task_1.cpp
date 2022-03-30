#include<iostream>
#include<future>
#include<thread>
#include<algorithm>
#include<vector>
#include<iomanip>

double integrate(double (*func)(double), double a, double b, double eps = pow(10, -6))
{
	double res{ 0 };
	for (double value = a; value <= b; value += eps)
	{
		res += func(value) * eps;
	}

	return res;
}

int main()
{
	return 0;
}