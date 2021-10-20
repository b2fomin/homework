#pragma once
#include<iostream>
#include<vector>

class Figure
{
protected:
	std::vector<std::pair<int, int>> figure;
	int size;
	virtual void calculate_figure()=0;
public:
	virtual ~Figure();
	virtual double perimetr() = 0;
	virtual double area() = 0;
	friend std::ostream& operator<<(std::ostream&, const Figure&);
};

class Polygon :public Figure {};

class Triangle :public Polygon
{
protected:
	double side1, side2, side3;
	virtual void calculate_figure() final;
public:
	Triangle(double, double, double);
	virtual ~Triangle() = default;
	virtual double perimetr() final;
	virtual double area() final;
};

class Quadrangle :public Polygon
{
protected:
	double side1, side2, side3, side4;
public:
	Quadrangle(double, double, double, double);
	virtual ~Quadrangle();
	virtual double perimetr() final;
	virtual double area() override = 0;
};

class Parallelogram :public Quadrangle
{
protected:
	double alpha;
	virtual void calculate_figure() final;
public:
	Parallelogram(double, double, double);
	virtual ~Parallelogram() = default;
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
	virtual void calculate_figure() final;
public:
	Ellipse(double, double);
	virtual ~Ellipse() = default;
	virtual double perimetr() final;
	virtual double area() final;
};

class Circle :public Ellipse
{
public:
	Circle(double);
};