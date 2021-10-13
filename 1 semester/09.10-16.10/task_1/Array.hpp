#pragma once
#include<iostream>
#include<utility>
#include<vector>

class Array
{
private:
	int* data;
	int size;
	std::vector<int> arr;
public:
	Array(int size);
	~Array();
	Array(const Array& other);
	Array(Array&& other);
};