#include<iostream>
#include<vector>
#include<string>

int main()
{
	std::vector<int> arr;
	for (int i = 1; i <= 10; ++i)
		arr.push_back(i);

	while(std::cin.peek()!='\n')
	{
		int number;
		std::cin >> number;
		arr.push_back(number);
		
	}

	return 0;
}