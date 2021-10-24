#include"Figure.hpp"
#include<iostream>

int main()
{
	std::vector<Figure*> arr{ new Triangle(18,10,10), new Parallelogram(5,6,M_PI / 6), new Ellipse(5,6) };
	for (auto& elem : arr)
	{
		elem->calculate_figure();
		std::cout << elem->perimeter() << '\t' << elem->area() << std::endl;
		std::cout << *elem;		
	}
}