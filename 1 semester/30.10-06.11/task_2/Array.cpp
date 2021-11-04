#include "Array.hpp"

template<class T>
Array<T>::Array() :
	size(0), capacity(1), arr(new T[1]) {};

template<class T>
Array<T>::Array(std::initializer_list<T> arr):
	size(arr.size()), capacity(arr.size()),
	arr(new T[size])
{
	int i = 0;
	for (auto& elem : arr)
	{
		arr[i] = elem;
		++i;
	}
}

template<class T>
Array<T>::Array(int size) :
	size(size), capacity(size), arr(new T[size]) {};
