#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>

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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(arr.begin(), arr.end(), gen);

	return 0;
}