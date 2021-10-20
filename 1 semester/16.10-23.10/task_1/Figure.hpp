#pragma once
#include<iostream>
#include<vector>

class Figure
{
protected:
	std::vector<std::pair<int, int>> figure;
	int size;
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
public:
	Triangle(double, double, double);
	virtual ~Triangle();
	virtual double perimetr() override;
	virtual double area() override;
};