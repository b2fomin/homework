#include "Array.hpp"

template<class T>
Array<T>::Array() :
	size(0), capacity(1), arr(new T[1]) {};

template<class T>
Array<T>::Array(std::initializer_list<T> arr) :
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
Array<T>::Array(const Array<T>& other) :
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
Array<T>::Array(Array<T>&& other) :
	size(other.size), capacity(other.capacity),
	arr(other.arr)
{
	other.arr = nullptr;
}

template<class T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
	if (other == *this) return *this;

	size = other.size;
	capacity = other.capacity;
	arr = other.arr;

	other.arr = nullptr;
}

template<class T>
void Array<T>::push_back(T value)
{
	++size;
	if (size > capacity)
	{
		capacity *= 2;
		T* old_arr = arr;
		arr = new T[capacity];

		for (int i = 0; i < size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}
	arr[size - 1] = value;
}

template<class T>
T Array<T>::pop(int index)
{
	--size;
	if (size * 2 < capacity)
	{
		capacity /= 2;
		T* old_arr = arr;
		arr = new T[capacity];

		for (int i = 0; i < size + 1; ++i)arr[i] = old_arr[i];
		delete[] old_arr;
	}

	T result = arr[index];
	for (int i = index; i < size - 1; ++i) arr[i] = arr[i + 1];
	return result;
}

template<class T>
int Array<T>::get_size() const noexcept { return size; }

template<class T>
int Array<T>::get_capacity() const noexcept { return capacity; }

template<class T>
void Array<T>::resize(int new_size)
{
	int old_size = size;
	size = new_size;
	while (size * 2 < capacity) capacity /= 2;
	while (size > capacity) capacity *= 2;

	T* old_arr = arr;
	arr = new T[capacity];

	for (int i = 0; i < old_size; ++i) arr[i] = old_arr[i];
	delete[] old_arr;
}

template<class T>
void Array<T>::insert(T value, int index)
{
	++size;
	if (size > capacity)
	{
		capacity *= 2;
		T* old_arr = arr;
		arr = new T[capacity];

		for (int i = 0; i < size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}

	T tmp = arr[index];
	arr[index] = value;
	for (int i = index + 1; i < size; ++i)
	{
		std::swap(tmp, arr[i]);
	}
}

template<class T>
T& Array<T>::operator[](int index)
{
	if ((index < 0) || (index >= size)) throw std::out_of_range("Invalid index");
	return arr[index];
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Array<T> arr)
{
	for (auto& elem : arr.arr) out << elem << '\t';
	return out;
}

template<class T>
Array<T> operator+(const Array<T>& left, const Array<T>& right)
{
	Array<T> new_arr;
	new_arr.size = left.size + right.size;
	new_arr.capacity = left.capacity + right.capacity;
	new_arr.arr = new T[new_arr.capacity];
	int i = 0;
	for (i; i < left.size; ++i) new_arr[i] = left.arr[i];
	for (i; i < new_arr.size++i) new_arr[i] = right.arr[i - left.size];

	return new_arr;
}