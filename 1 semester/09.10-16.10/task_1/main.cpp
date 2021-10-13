#include<iostream>
#include<vector>
#include"Array.hpp"

void foo(Array arr)
{
	std::cout << arr;
}

int main()
{
	using namespace std;
	vector<int> v1{ 1,2,3 };
	vector<int> v2{ 4,5,6 };
	Array arr1{4};
	Array arr2{3};

	arr1.set_arr(v1);
	arr2.set_arr(v2);

	for (int i = 1; i < 4; ++i) arr1[i]=i;
	for (int i = 4; i < 7; ++i) arr2[i]=i;

	Array arr3{ arr1 };
	arr2 = arr1;
	cout << arr1 << arr2 << endl;
	foo(arr3);

	return 0;
}