#include "Figure.hpp"

std::ostream& operator<<(std::ostream& out, const Figure& figure)
{
	for (int i = 0; i < figure.size; ++i)
	{
		static int current = 0;
		for (int j = 0; j < figure.size; ++j)
		{
			if (j != figure.figure[current].first) out << " ";
			else
			{
				out << "*";
				++current;
			}
		}
		out << std::endl;
	}
}

Triangle::Triangle(double side1, double side2, double side3) : side1(side1), side2(side2), side3(side3) {};

double Triangle::perimetr()
{
	return side1 + side2 + side3;
}

double Triangle::area()
{
	double p = (side1 + side2 + side3) / 2;
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

Quadrangle::Quadrangle(double side1, double side2, double side3, double side4) :
	side1(side1), side2(side2), side3(side3), side4(side4)
{

}

double Quadrangle::perimetr()
{
	return side1 + side2 + side3 + side4;
}

