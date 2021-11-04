#include "Array.hpp"

int main()
{
	Array<int> arr{1,2,3,4,5};

	std::cout << arr << std::endl;
	arr.push_back(6);
	std::cout << arr << std::endl;
	arr.pop(0);
	std::cout << arr << std::endl;
	arr.resize(8);
	std::cout << arr << std::endl;
	arr.insert(4, 2);
	std::cout << arr << std::endl;
	return 0;
}