#pragma once
#include<iostream>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<algorithm>

class Figure
{
protected:
	std::vector<std::pair<int, int>> figure;
	int size;
public:
	virtual void calculate_figure() = 0;
	virtual ~Figure()=default;
	virtual double perimeter() = 0;
	virtual double area() = 0;
	friend std::ostream& operator<<(std::ostream&, const Figure&);
};

class Polygon :public Figure {};

class Triangle :public Polygon
{
protected:
	double side1, side2, side3;
public:
	virtual void calculate_figure() final;
	Triangle(double, double, double);
	virtual ~Triangle() = default;
	virtual double perimeter() final;
	virtual double area() final;
};

class Quadrangle :public Polygon
{
protected:
	double side1, side2, side3, side4;
public:
	Quadrangle(double, double, double, double);
	virtual ~Quadrangle() = default;
	virtual double perimeter() final;
};

class Parallelogram :public Quadrangle
{
protected:
	double alpha;
public:
	virtual void calculate_figure() final;
	Parallelogram(double, double, double);
	virtual double area() final;
};

class Rhombus :public Parallelogram
{
public:
	Rhombus(double, double);
};

class Rectangle :public Parallelogram
{
public:
	Rectangle(double, double);
};

class Square :public Rectangle
{
public:
	Square(double);
};

class Ellipse : public Figure
{
protected:
	double radius1, radius2;
public:
	virtual void calculate_figure() final;
	Ellipse(double, double);
	virtual ~Ellipse() = default;
	virtual double perimeter() override;
	virtual double area() final;
};

class Circle :public Ellipse
{
public:
	Circle(double);
	virtual double perimeter() final;
};