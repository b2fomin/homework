#include"Figure.hpp"
#include<iostream>

int main()
{
	std::vector<Figure*> arr{ new Triangle(5,7,7), new Parallelogram(5,6,M_PI / 6), new Ellipse(6,10) };
	for (auto& elem : arr)
	{
		elem->calculate_figure();
		std::cout << elem->perimeter() << '\t' << elem->area() << std::endl;
		std::cout << *elem;		
	}
}