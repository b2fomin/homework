#include "Figure.hpp"

std::ostream& operator<<(std::ostream& out, const Figure& figure)
{
	int current = 0;
	for (int i = 0; i < figure.size; ++i)
	{
		for (int j = 0; j < figure.size; ++j)
		{
			if (j != figure.figure[current].first) out << " ";
			else
			{
				out << "*";
				if (current < figure.figure.size() - 1)
					while ((j == figure.figure[current].first)&&(figure.figure[current].second == i)) ++current;
				else return out << std::endl;
			}
		}
		out << std::endl;
	}
	return out;
}

Triangle::Triangle(double side1, double side2, double side3) : side1(side1), side2(side2), side3(side3)
{

}

double Triangle::perimeter()
{
	return side1 + side2 + side3;
}

void Triangle::calculate_figure()
{
	std::vector<double> arr{ side1, side2, side3 };
	size = 3 * round(*std::max_element(arr.begin(), arr.end()));
	double cos_alpha_1 = (side1 * side1 + side2 * side2 - side3 * side3) / (2 * side1 * side2);
	double sin_alpha_1 = sqrt(1 - cos_alpha_1 * cos_alpha_1);
	double cos_alpha_2 = (side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3);
	double sin_alpha_2 = sqrt(1 - cos_alpha_2 * cos_alpha_2);

	int x_0 = size / 2 - round(side1 / 2);
	//side 1
	for (int i = 0; i < side1; ++i)
	{
		figure.push_back(std::make_pair(x_0 + i, 0));
	}
	//side 2
	for (int i = 0; i < side2; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 + i * cos_alpha_1), round(i * sin_alpha_1)));
	}
	x_0 += round(side1);
	//side 3
	for (int i = 0; i < side2; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 - i * cos_alpha_2), round(i * sin_alpha_2)));
	}
	std::sort(figure.begin(), figure.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {return (p1.second < p2.second) || ((p1.second == p2.second) && (p1.first < p2.first)); });
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

double Quadrangle::perimeter()
{
	return side1 + side2 + side3 + side4;
}

Parallelogram::Parallelogram(double side1, double side2, double alpha) :Quadrangle(side1, side2, side1, side2), alpha(alpha)
{

}

double Parallelogram::area()
{
	return side1 * side2 * sin(alpha);
}

void Parallelogram::calculate_figure()
{
	size = 3 * round(std::max(side1, side2));
	double cos_alpha = cos(alpha);
	double sin_alpha = sin(alpha);

	double x_0 = size / 2 - round(side1 / 2);
	double y_0 = 0;
	//side 1
	for (int i = 0; i < side1; ++i)
	{
		figure.push_back(std::make_pair(x_0 + i, y_0));
	}
	//side 2
	for (int i = 0; i < side2; ++i)
	{
		figure.push_back(std::make_pair(round(x_0 + i * cos_alpha), round(y_0 + i * sin_alpha)));
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
		figure.push_back(std::make_pair(round(x_0 + i * cos_alpha), round(y_0 + i * sin_alpha)));
	}
	std::sort(figure.begin(), figure.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {return (p1.second < p2.second) || ((p1.second == p2.second) && (p1.first < p2.first)); });
}

Rhombus::Rhombus(double side, double alpha) :Parallelogram(side, side, alpha) {};
Rectangle::Rectangle(double side1, double side2) :Parallelogram(side1, side2, M_PI / 2) {};
Square::Square(double side) :Rectangle(side, side) {};

Ellipse::Ellipse(double radius1, double radius2) :radius1(std::max(radius1, radius2)), radius2(std::min(radius1, radius2))
{

}

double Ellipse::perimeter()
{
	return 4 * (M_PI * radius1 * radius2 + (radius1 - radius2)) / (radius1 + radius2);
}

double Ellipse::area()
{
	return M_PI * radius1 * radius2;
}

void Ellipse::calculate_figure()
{
	size = 3 * round(radius1);
	int x_0 = 2 * round(radius1);
	int y_0 = 2 * round(radius2);
	for (int i = -round(radius1); i < round(radius1); ++i)
	{
		figure.push_back(std::make_pair(x_0 + i, round(y_0 + radius2 * sqrt(1 - i * i / (radius1 * radius1)))));
		figure.push_back(std::make_pair(x_0 + i, round(y_0 - radius2 * sqrt(1 - i * i / (radius1 * radius1)))));
	}
	std::sort(figure.begin(), figure.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {return (p1.second < p2.second) || ((p1.second == p2.second) && (p1.first < p2.first)); });
}

Circle::Circle(double radius) :Ellipse(radius, radius) {};

double Circle::perimeter()
{
	return 2 * M_PI * radius1;
}