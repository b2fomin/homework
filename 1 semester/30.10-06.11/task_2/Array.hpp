#pragma once
#include<iostream>
#include<exception>

template<class T>
class Array
{
private:
	size_type m_capacity;
	size_type m_size;
	iterator arr;
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

	using iterator = pointer;
	using const_iterator = const_pointer;

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
	void insert(T, size_type);
	void resize(size_type);

	size_type size() const noexcept;
	size_type capacity() const noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

	friend std::ostream& operator<<(std::ostream&, const Array<T>);
	friend Array<T> operator+(const Array<T>&, const Array<T>&);
	Array<T>& operator+=(const Array<T>&);
	reference operator[](size_type);
	const_reference operator[](size_type) const;
};