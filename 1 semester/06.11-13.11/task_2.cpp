#include<iostream>
#include<vector>

template<typename Type,typename... Args>
Type* new_object(Args... args)
{
	return new Type(args...);
}

int main()
{
	auto arr1 = *new_object<std::vector<int>>(5);
	auto arr2 = new_object<std::vector<int>>();
	for (int i = 0; i < 5; ++i) std::cout << arr1[i] << std::endl;
	std::cout << arr2;
	return 0;
}