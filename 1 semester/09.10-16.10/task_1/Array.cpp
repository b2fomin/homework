#include"Array.hpp"

Array::Array(int size):size(size)
{
	data = new int[size];
	arr.resize(size);
}