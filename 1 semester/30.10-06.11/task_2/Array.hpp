#pragma once
#include<iostream>
#include<exception>

template<class T>
class Array
{
private:
	int m_capacity;
	int m_size;
	T* arr;
public:

	Array();
	Array(std::initializer_list<T>);
	Array(int);

	~Array();
	Array(const Array<T>&);
	Array<T>& operator=(const Array<T>&);
	Array(Array<T>&&);
	Array<T>& operator=(Array<T>&&);

	void push_back(T);
	T pop(int);
	void insert(T, int);
	void resize(int);

	int size() const noexcept;
	int capacity() const noexcept;
	T* begin() const noexcept;
	T* end() const noexcept;

	friend std::ostream& operator<<(std::ostream&, const Array<T>);
	friend Array<T> operator+(const Array<T>&, const Array<T>&);
	Array<T>& operator+=(const Array<T>&);
	T& operator[](int);
	T& operator[](int) const;
};