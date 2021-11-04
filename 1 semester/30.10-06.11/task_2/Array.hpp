#pragma once
#include<iostream>
#include<exception>

template<class T>
class Array
{
private:
	int capacity;
	int size;
	T* arr;
public:
	Array();
	Array(std::initializer_list<T>);
	Array(int size);

	~Array();
	Array(const Array<T>&);
	Array<T>& operator=(const Array<T>&);
	Array(Array<T>&&);
	Array<T>& operator=(Array<T>&&);

	void push_back(T);
	T pop(int);
	void insert(T, int);
	void resize(int);

	int get_size() const noexcept;
	int get_capacity() const noexcept;

	friend std::ostream& operator<<(std::ostream&, const Array<T>);
	friend std::istream& operator>>(std::istream&, Array<T>);
	friend Array<T> operator+(const Array<T>&, const Array<T>&);
	T& operator[](int);

};