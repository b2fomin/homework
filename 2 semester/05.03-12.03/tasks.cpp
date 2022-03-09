#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>

template<typename T>
void print_vector(std::vector<T> arr)
{
	for (auto& elem : arr)
		std::cout << elem << " ";

	std::cout << std::endl;
}

int main()
{
	std::vector<int> arr;
	for (int i = 1; i <= 10; ++i)
		arr.push_back(i);

	print_vector(arr);

	while (std::cin.peek() != '\n')
	{
		int number;
		std::cin >> number;
		arr.push_back(number);

	}

	print_vector(arr);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(arr.begin(), arr.end(), gen);

	print_vector(arr);

	arr.erase(std::unique(arr.begin(), arr.end()), arr.end());// can be deleted
	for (int i = 0; i < arr.size(); ++i)
	{
		arr.erase(std::remove(arr.begin() + i + 1, arr.end(), arr[i]), arr.end());
	}

	print_vector(arr);

	std::cout << std::count_if(arr.begin(), arr.end(), [](const auto& elem) {return elem % 2; }) << std::endl;

	std::cout << "min: " << *std::min_element(arr.begin(), arr.end()) << ", max: " << *std::max_element(arr.begin(), arr.end()) << std::endl;

	std::cout << *std::find_if(arr.begin(), arr.end(), [](const auto& elem)
		{
			if (elem <= 1)
				return false;

			for (int i = 2; i * i <= elem; ++i)
				if (elem % i == 0)
					return false;

			return true;
		}) << std::endl;

	return 0;
}