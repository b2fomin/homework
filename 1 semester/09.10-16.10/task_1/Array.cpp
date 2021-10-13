#include"Array.hpp"

Array::Array(int size,std::vector<int> arr) :size(size), arr(arr)
{
	data = new int[size];
}

Array::~Array()
{
	delete[] data;
}

Array::Array(const Array& other) :size(other.size), arr(other.arr)
{
	data = new int[size];
	for (int i = 0; i < size; ++i) data[i] = other.data[i];
}

Array::Array(Array&& other) :size(other.size), data(other.data)
{
	arr = std::move(other.arr);
	other.data = nullptr;
}

Array& Array::operator=(const Array& other)
{
	if (&other == this) return *this;

	delete[] data;
	size = other.size;
	arr = other.arr;
	data = new int[size];
	for (int i = 0; i < size; ++i) data[i] = other.data[i];
	return *this;
}

void Array::set_arr(std::vector<int> arr)
{
	this->arr = arr;
}

void Array::append(int value)
{
	int* old_data = data;
	data = new int[++size];

	for (int i = 0; i < size - 1; ++i) data[i] = old_data[i];
	data[size - 1] = value;
}