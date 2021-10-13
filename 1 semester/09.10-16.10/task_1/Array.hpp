#pragma once
#include<iostream>
#include<vector>
#include<utility>

class Array
{
private:
	int* data;
	int size;
	std::vector<int> arr;
public:
	void set_arr(std::vector<int> arr);
	void append(int value);
	friend std::ostream& operator<<(std::ostream& out, const Array& other);

	int get_size() const;
	int* get_data() const;
	std::vector<int> get_arr() const;

	Array(int size = 0, std::vector<int> arr = std::vector<int>(0));
	~Array();
	Array(const Array& other);
	Array(Array&& other);
	Array& operator=(const Array& other);
	Array& operator=(Array&& other);
	int& operator[](const int index);
};