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

template<class T>
Array<T>::~Array()
{
	delete[] arr;
}

template<class T>
Array<T>::Array(const Array<T>& other):
	size(other.size), capacity(other.capacity),
	arr(new T[capacity])
{
	for (int i = 0; i < capacity; ++i) arr[i] = other.arr[i];
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (other == *this) return *this;

	size = other.size;
	capacity = other.capacity;
	arr = new T[capacity];

	for (int i = 0; i < capacity; ++i) arr[i] = other.arr[i];

	return *this;
}

template<class T>
Array<T>::Array(Array<T>&& other):
	size(other.size),capacity(other.capacity),
	arr(other.arr)
{
	other.arr = nullptr;
}

template<class T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
	if(other == *this) return *this;

	size = other.size;
	capacity = other.capacity;
	arr = other.arr;

	other.arr = nullptr;
}