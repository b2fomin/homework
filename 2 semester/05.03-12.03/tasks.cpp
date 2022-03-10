#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>
#include<numeric>

template<typename T>
void print_vector(std::vector<T> arr)
{
	for (auto& elem : arr)
		std::cout << elem << " ";

	std::cout << std::endl;
}

int main()
{
	std::cout << "Task 1:" << std::endl;

	std::vector<int> arr;
	for (int i = 1; i <= 10; ++i)
		arr.push_back(i);

	print_vector(arr);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 2:" << std::endl;

	while (std::cin.peek() != '\n')
	{
		int number;
		std::cin >> number;
		arr.push_back(number);

	}

	print_vector(arr);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 3:" << std::endl;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(arr.begin(), arr.end(), gen);

	print_vector(arr);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 4:" << std::endl;

	arr.erase(std::unique(arr.begin(), arr.end()), arr.end());// can be deleted
	for (int i = 0; i < arr.size(); ++i)
	{
		arr.erase(std::remove(arr.begin() + i + 1, arr.end(), arr[i]), arr.end());
	}

	print_vector(arr);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 5:" << std::endl;

	std::cout << std::count_if(arr.begin(), arr.end(), [](const auto& elem) {return elem % 2; }) << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 6:" << std::endl;
	
	std::cout << "min: " << *std::min_element(arr.begin(), arr.end()) << ", max: " << *std::max_element(arr.begin(), arr.end()) << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 7:" << std::endl;

	auto prime_iterator = std::find_if(arr.begin(), arr.end(), [](const auto& elem)
		{
			if (elem <= 1)
				return false;

			for (int i = 2; i * i <= elem; ++i)
				if (elem % i == 0)
					return false;

			return true;
		});

	if (prime_iterator != arr.end())
		std::cout << "Prime number is " << *prime_iterator << std::endl;
	else std::cout << "There's no prime number" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 8:" << std::endl;

	std::transform(arr.begin(), arr.end(), arr.begin(), [](const auto& elem) {return elem * elem; });

	print_vector(arr);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 9:" << std::endl;

	std::vector<int> arr2;

	for (int i = 0; i < arr.size(); ++i)
		arr2.push_back(gen() % 1000);

	print_vector(arr2);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Task 10:" << std::endl;

	std::cout << "sum: " << std::accumulate(arr2.begin(), arr2.end(), 0) << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}