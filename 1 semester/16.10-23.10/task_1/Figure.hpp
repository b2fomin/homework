#pragma once
#include<iostream>
#include<vector>

class Figure
{
protected:
	std::vector<int> figure;
public:
	virtual ~Figure();
	virtual int perimetr() = 0;
	virtual int area() = 0;
	friend std::ostream& operator<<(std::ostream& out, const Figure& figure);
};