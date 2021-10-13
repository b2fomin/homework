#include"Array.hpp"

Array::Array(int size) :size(size)
{
	data = new int[size];
	arr.resize(size);
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

Array::Array(Array&& other) :size(other.size), arr(other.arr), data(other.data)
{
	other.data = nullptr;
}