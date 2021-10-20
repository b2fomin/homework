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

Triangle::Triangle(double side1, double side2, double side3) : side1(side1), side2(side2), side3(side3)
{
	calculate_figure();
}

double Triangle::perimetr()
{
	return side1 + side2 + side3;
}

void Triangle::calculate_figure()
{
	size = 3*std::max(side1, side2, side3);
	double cos_alpha_1 = (side1 * side1 + side2 * side2 - side3 * side3) / (2 * side1 * side2);
	double sin_alpha_1 = sqrt(1 - cos_alpha_1 * cos_alpha_1);
	double cos_alpha_2= (side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3);
	double sin_alpha_1 = sqrt(1 - cos_alpha_2 * cos_alpha_2);

	int x_0 = size / 2 - round(side1/2);
	//side 1
	for (int i = 0; i < side1; ++i)
	{
		figure.push_back(std::make_pair(x_0+i,0));
	}
	//side 2
	for (int i = 0; i < side2; ++i)
	{
		figure.push_back(std::make_pair(x_0+round(i*cos_alpha_1), round(i*sin_alpha_1)));
	}
	x_0 += side1;
	//side 3
	for (int i = 0; i < side3; ++i)
	{
		figure.push_back(std::make_pair(x_0 - round(i * cos_alpha_1), round(i * sin_alpha_1)));
	}
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

Parallelogram::Parallelogram(double side1, double side2, double alpha) :Quadrangle(side1, side2, side1, side2), alpha(alpha)
{
	calculate_figure();
}

double Parallelogram::area()
{
	return side1 * side2 * sin(alpha);
}

void Parallelogram::calculate_figure()
{
	size = 3*std::max(side1, side2);
	double cos_alpha = cos(alpha);
	double sin_alpha = sin(alpha);

	double x_0 = size / 2 - round(side1/2);
	double y_0 = 0;
	//side 1
	for (int i = 0; i < side1; ++i)
	{
		figure.push_back(std::make_pair(x_0 + i, y_0));
	}
	//side 2
	for (int i = 0; i < side2; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 + i*cos_alpha), round(y_0 + i*sin_alpha)));
	}
	x_0 += round(side2 * cos_alpha);
	y_0 += round(side2 * sin_alpha);
	//side 3
	for (int i = 0; i < side3; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 + i), round(y_0 + i * sin_alpha)));
	}
	x_0 = size / 2 + round(side1 / 2);
	y_0 = 0;
	//side 4
	for (int i = 0; i < side4; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 - i), round(y_0 + i * sin_alpha)));
	}
}