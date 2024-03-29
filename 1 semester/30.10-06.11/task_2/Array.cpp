#pragma once
#include<iostream>
#include<exception>

template<class T>
class Array
{
public:
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

	Array();
	Array(std::initializer_list<T>);
	Array(size_type);

	~Array();
	Array(const Array<T>&);
	Array<T>& operator=(const Array<T>&);
	Array(Array<T>&&);
	Array<T>& operator=(Array<T>&&);

	void push_back(value_type);
	T pop(size_type);
	void insert(value_type, size_type);
	void resize(size_type);

	size_type size() const noexcept;
	size_type capacity() const noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	iterator begin() noexcept;
	iterator end() noexcept;

	template<class U>
	friend std::ostream& operator<<(std::ostream&, const Array<U>);
	template<class U>
	friend Array<U> operator+(const Array<U>&, const Array<U>&);
	Array<T>& operator+=(const Array<T>&);
	reference operator[](size_type);
	const_reference operator[](size_type) const;
private:
	size_type m_capacity;
	size_type m_size;
	iterator arr;
};

template<class T>
Array<T>::Array() =default;

template<class T>
Array<T>::Array(std::initializer_list<T> array) :
	m_size(array.size()), m_capacity(array.size()),
	arr(new T[m_size])
{
	size_type i = 0;
	for (auto& elem : array)
	{
		arr[i] = elem;
		++i;
	}
}

template<class T>
Array<T>::Array(size_type size) :
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
	for (size_type i = 0; i < m_capacity; ++i) arr[i] = other.arr[i];
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (other == *this) return *this;

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	arr = new T[m_capacity];

	for (size_type i = 0; i < m_capacity; ++i) arr[i] = other.arr[i];

	return *this;
}

template<class T>
Array<T>::Array(Array<T>&& other) :
	m_size(other.m_size), m_capacity(other.m_capacity),
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
void Array<T>::push_back(value_type value)
{
	++m_size;
	if (m_size > m_capacity)
	{
		m_capacity *= 2;
		iterator old_arr = arr;
		arr = new T[m_capacity];

		for (size_type i = 0; i < m_size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}
	arr[m_size - 1] = value;
}

template<class T>
typename Array<T>::value_type Array<T>::pop(size_type index)
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
	--m_size;
	if (m_size * 2 < m_capacity)
	{
		m_capacity /= 2;
		iterator old_arr = arr;
		arr = new T[m_capacity];

		for (size_type i = 0; i < m_size + 1; ++i)arr[i] = old_arr[i];
		delete[] old_arr;
	}

	value_type result = arr[index];
	for (size_type i = index; i < m_size+1; ++i) arr[i] = arr[i + 1];
	return result;
}

template<class T>
typename Array<T>::size_type Array<T>::size() const noexcept { return m_size; }

template<class T>
typename Array<T>::size_type Array<T>::capacity() const noexcept { return m_capacity; }

template<class T>
typename Array<T>::const_iterator Array<T>::begin() const noexcept { return arr; }

template<class T>
typename Array<T>::const_iterator Array<T>::end() const noexcept { return arr + m_size; }

template<class T>
typename Array<T>::iterator Array<T>::begin() noexcept { return arr; }

template<class T>
typename Array<T>::iterator Array<T>::end() noexcept { return arr + m_size; }

template<class T>
void Array<T>::resize(size_type new_size)
{
	if (new_size < 0) throw std::underflow_error("Negative size");
	size_type old_size = m_size;
	m_size = new_size;
	while (m_size * 2 < m_capacity) m_capacity /= 2;
	while (m_size > m_capacity) m_capacity *= 2;

	iterator old_arr = arr;
	arr = new T[m_capacity];

	for (size_type i = 0; i < old_size; ++i) arr[i] = old_arr[i];
	delete[] old_arr;
}

template<class T>
void Array<T>::insert(value_type value, size_type index)
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
	++m_size;
	if (m_size > m_capacity)
	{
		m_capacity *= 2;
		iterator old_arr = arr;
		arr = new T[m_capacity];

		for (size_type i = 0; i < m_size - 1; ++i) arr[i] = old_arr[i];
		delete[] old_arr;
	}

	value_type tmp = arr[index];
	arr[index] = value;
	for (size_type i = index + 1; i < m_size; ++i)
	{
		std::swap(tmp, arr[i]);
	}
}

template<class T>
typename Array<T>::reference Array<T>::operator[](size_type index)
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
	return arr[index];
}

template<class T>
typename Array<T>::const_reference Array<T>::operator[](size_type index) const
{
	if ((index < 0) || (index >= m_size)) throw std::out_of_range("Invalid index");
	return arr[index];
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Array<T> arr)
{
	for (typename Array<T>::size_type i = 0; i < arr.size();++i) out << arr.arr[i] << '\t';
	return out;
}

template<class T>
Array<T> operator+(const Array<T>& left, const Array<T>& right)
{
	Array<T> new_arr;
	new_arr.m_size = left.m_size + right.m_size;
	new_arr.m_capacity = left.m_capacity + right.m_capacity;
	new_arr.arr = new T[new_arr.m_capacity];
	typename Array<T>::size_type i = 0;
	for (i; i < left.m_size; ++i) new_arr[i] = left.arr[i];
	for (i; i < new_arr.m_size; ++i) new_arr[i] = right.arr[i - left.m_size];

	return new_arr;
}

template<class T>
Array<T>& Array<T>::operator+=(const Array<T>& other)
{
	return *this = operator+(*this, other);
}