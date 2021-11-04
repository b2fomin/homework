#include "Array.hpp"

template<class T>
Array<T>::Array() :
	m_size(0), m_capacity(1), arr(new T[1]) {};

template<class T>
Array<T>::Array(std::initializer_list<T> arr) :
	m_size(arr.size()), m_capacity(arr.size()),
	arr(new T[m_size])
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
	m_size(size), m_capacity(size), arr(new T[size]) {};

template<class T>
Array<T>::~Array()
{
	delete[] arr;
}

template<class T>
Array<T>::Array(const Array<T>& other) :
	m_size(other.m_size), m_capacity(other.m_capacity),
	arr(new T[m_capacity])
{
	for (int i = 0; i < m_capacity; ++i) arr[i] = other.arr[i];
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (other == *this) return *this;

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	arr = new T[m_capacity];

	for (int i = 0; i < m_capacity; ++i) arr[i] = other.arr[i];

	return *this;
}

template<class T>
Array<T>::Array(Array<T>&& other) :
	m_size(other.m_size), capacity(other.m_capacity),
	arr(other.arr)
{
	other.arr = nullptr;
}

template<class T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
	if (other == *this) return *this;

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	arr = other.arr;

	other.arr = nullptr;
}

template<class T>
void Array<T>::push_back(T value)
{
	++m_size;
	if (m_size > m_capacity)
	{
		m_capacity *= 2;
		T* old_arr = arr;
		arr = new T[m_capacity];

		for (int i = 0; i < m_size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}
	arr[m_size - 1] = value;
}

template<class T>
T Array<T>::pop(int index)
{
	--m_size;
	if (m_size * 2 < m_capacity)
	{
		m_capacity /= 2;
		T* old_arr = arr;
		arr = new T[m_capacity];

		for (int i = 0; i < m_size + 1; ++i)arr[i] = old_arr[i];
		delete[] old_arr;
	}

	T result = arr[index];
	for (int i = index; i < m_size - 1; ++i) arr[i] = arr[i + 1];
	return result;
}

template<class T>
int Array<T>::size() const noexcept { return size; }

template<class T>
int Array<T>::capacity() const noexcept { return capacity; }

template<class T>
void Array<T>::resize(int new_size)
{
	int old_size = m_size;
	m_size = new_size;
	while (m_size * 2 < m_capacity) m_capacity /= 2;
	while (m_size > m_capacity) m_capacity *= 2;

	T* old_arr = arr;
	arr = new T[m_capacity];

	for (int i = 0; i < old_size; ++i) arr[i] = old_arr[i];
	delete[] old_arr;
}

template<class T>
void Array<T>::insert(T value, int index)
{
	++m_size;
	if (m_size > m_capacity)
	{
		m_capacity *= 2;
		T* old_arr = arr;
		arr = new T[m_capacity];

		for (int i = 0; i < m_size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}

	T tmp = arr[index];
	arr[index] = value;
	for (int i = index + 1; i < m_size; ++i)
	{
		std::swap(tmp, arr[i]);
	}
}

template<class T>
T& Array<T>::operator[](int index)
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
	return arr[index];
}

template<class T>
T& Array<T>::operator[](int index) const
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
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
	new_arr.m_size = left.m_size + right.m_size;
	new_arr.m_capacity = left.m_capacity + right.m_capacity;
	new_arr.arr = new T[new_arr.m_capacity];
	int i = 0;
	for (i; i < left.m_size; ++i) new_arr[i] = left.arr[i];
	for (i; i < new_arr.m_size; ++i) new_arr[i] = right.arr[i - left.m_size];

	return new_arr;
}

template<class T>
Array<T>& Array<T>::operator+=(const Array<T>& other)
{
	return *this = operator+(*this, other);
}