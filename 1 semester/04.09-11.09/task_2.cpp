#include <iostream>

const double RATES[8] = { 0.01, 0.001, 1, 0.01, 0.01, pow(10,-5),
pow(10,-7), 0.1 };

int main()
{
	using namespace std;

	cout << "What would you like to convert (enter number)?" << endl;
	cout << "lenght (m) --- 1" << endl;
	cout << "mass (kg) --- 2" << endl;
	cout << "time (s) --- 3" << endl;
	cout << "velocity (m/s) --- 4" << endl;
	cout << "acceleration (m/s^2) --- 5" << endl;
	cout << "force (N) --- 6" << endl;
	cout << "energy (J) --- 7" << endl;
	cout << "pressure (Pa) --- 8" << endl;

	int number = 0;
	double value = 0;
	cin >> number;
	
	while (!(number > 0 && number < 9)) {
		cout << "Sorry, but you've put wrong number. Try again." << endl;
		cin >> number;
	}

	cout << "What's the value of this variable?" << endl;
	cin >> value;

	cout << "Result is " << value * RATES[number - 1];

	return 0;
}