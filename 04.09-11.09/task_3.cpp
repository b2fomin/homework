#include <iostream>

int main()
{
	using namespace std;
	double a, b, c = 0.0;

	cout << "Input coefficients a,b and c" << endl;
	cin >> a >> b >> c;

	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0) cout << "There are infinite solutions";
			else cout << "There is no solution";
		}
		else cout << "There is one solution: x = " << -c / b;
		return 0;
	}

	double D = pow(b, 2) - 4 * a * c;

	if (D < 0) cout << "There is no solution";
	else if (D == 0) cout << "There is one solution: x = " << -b / (2 * a);
	else cout << "There are two solutions: x1 = " << (-b + D) / (2 * a) << "; x2 = " << (-b - D) / (2 * a);
	
	return 0;
}