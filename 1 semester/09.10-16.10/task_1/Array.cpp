#include"Array.hpp"

Array::Array(int size, std::vector<int> arr) :size(size), arr(arr)
{
	data = new int[size];
	for (int i = 0; i < size; ++i) data[i] = 0;
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

Array::Array(Array&& other) :size(other.size), data(other.data), arr(std::move(other.arr))
{
	other.data = nullptr;
}

Array& Array::operator=(const Array& other)
{
	if (&other == this) return *this;

	delete[] data;
	size = other.size;
	arr = other.arr;
	data = new int[size];
	for (int i = 0; i < size; ++i) data[i] = other.data[i];
	return *this;
}

Array& Array::operator=(Array&& other)
{
	if (&other == this) return *this;

	delete[] data;
	size = other.size;
	arr = std::move(other.arr);
	data = other.data;
	other.data = nullptr;
	return *this;
}

void Array::set_arr(std::vector<int> arr)
{
	this->arr = arr;
}

void Array::append(int value)
{
	int* old_data = data;
	data = new int[++size];

	for (int i = 0; i < size - 1; ++i) data[i] = old_data[i];
	data[size - 1] = value;
	delete[] old_data;
}

std::ostream& operator<<(std::ostream& out, const Array& other)
{
	out << "Size of array: " << other.size << std::endl;
	out << "Vector of array: ";
	for (auto& elem : other.arr) out << elem << '\t';
	out << std::endl << "Data of array: ";
	for (int i = 0; i < other.size; ++i) out << other.data[i] << '\t';
	return out << std::endl;
}

int& Array::operator[](const int index) const
{
	return data[index];
}

int Array::get_size() const { return size; };
int* Array::get_data() const { return data; };
std::vector<int> Array::get_arr() const { return arr; };
