#include<iostream>

template<class Derived>
class Base
{
public:
	void print()
	{
		self()->printImpl();
	}
private:
	Derived* self()
	{
		return static_cast<Derived*>(this);
	}
};

class Circle : public Base<Circle>
{
	friend Base<Circle>;
public:
	void printImpl()
	{
		std::cout << "printing circle..." << std::endl;
	}
};

class Triangle :public Base<Triangle>
{
	friend Base<Triangle>;
public:
	void printImpl()
	{
		std::cout << "printing triangle..." << std::endl;
	}
};

int main()
{
	Base<Circle> circle;
	Base<Triangle> triangle;
	circle.print();
	triangle.print();
	return 0;
}