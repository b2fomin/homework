#include<iostream>
#include<vector>

int main()
{
	std::vector<int> arr{ 1,1,1 };
	std::cout << "Capacity is " << arr.capacity() << std::endl;

	arr.reserve(10);
	std::cout << "Manually changed capacity is " << arr.capacity() << std::endl;

	return 0;
}