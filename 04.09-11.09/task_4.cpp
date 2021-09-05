#include <iostream>

int main()
{
	int x = 5, y = 9;
	std::cout << "x= " << x << ", y= " << y << std::endl;
	x += y;
	y = x - y;
	x -= y;

	std::cout << "x= " << x << ", y= " << y;

	return 0;
}