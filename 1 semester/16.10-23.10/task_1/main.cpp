#include"Figure.hpp"
#include<iostream>

int main()//now work only with one figure
{
	std::vector<Figure*> arr{ new Triangle(9,5,5), new Parallelogram(5,6,M_PI / 6), new Ellipse(5,6) };
	for (auto& elem : arr)
	{
		std::cout << elem->perimetr() << '\t' << elem->area() << std::endl;
	}
	std::cout << *arr[0];
}