#pragma once
#include<vector>

class Array
{
private:
	int* data;
	int size;
	std::vector<int> arr;
public:
	void set_arr(std::vector<int> arr);
	void append(int value);

	int get_size() const;
	int* get_data() const;
	std::vector<int> get_arr() const;

	Array(int size = 0, std::vector<int> arr = std::vector<int>(0));
	~Array();
	Array(const Array& other);
	Array(Array&& other);
	Array& operator=(const Array& other);
};