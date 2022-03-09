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

	arr.erase(std::unique(arr.begin(), arr.end()), arr.end());// can be deleted
	for (int i = 0; i < arr.size(); ++i)
	{
		arr.erase(std::remove(arr.begin() + i+1, arr.end(), arr[i]), arr.end());
	}

	std::cout << std::count_if(arr.begin(), arr.end(), [](const auto& elem) {return elem % 2; }) << std::endl;

	std::cout << "min: " << *std::min_element(arr.begin(), arr.end()) << ", max: " << *std::max_element(arr.begin(), arr.end());

	return 0;
}