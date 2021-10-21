#include"Figure.hpp"
#include<iostream>

int main()//now work only with one figure
{
	Figure* fig = new Parallelogram(4, 5, M_PI / 6);
	std::cout << *fig;
}