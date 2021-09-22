#include <iostream>
#include<functional>
#include <vector>

double calculate(double x, double y, std::function<double(double, double)> calculator)
{
	return calculator(x, y);
}

int main()
{
	using namespace std;

	vector<function<double(double, double)>> functions{
		[](double x, double y) {return x + y; },
		[](double x, double y) {return x - y; },
		[](double x, double y) {return x * y; },
		[](double x, double y) {return x / y; }
	};

	cout << "Enter two numbers: ";
	double x, y;
	cin >> x >> y;
	
	for (int i = 0; i < functions.size(); i++) cout << "Result of function number " << i << " is " << calculate(x, y, functions[i]) << endl;

	return 0;
}