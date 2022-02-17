#include<iostream>
#include <boost/multi_array.hpp>
#include<vector>

template<typename T>
std::vector<int> calculate_dimensions(std::vector<T>& vector)
{
	std::vector<int> dimensions;
	dimensions.push_back(vector.size());
	return dimensions;
}

template<typename T>
std::vector<int> calculate_dimensions(std::vector<std::vector<T>>& vector)
{
	std::vector<int> dimensions=calculate_dimensions(vector[0]);
	dimensions.push_back(vector.size());
	return dimensions;
}

template<typename T1, int Dimensions, typename T2>
auto create_multi_array(std::vector<T2>& vector)
{
	std::vector<int> dimensions = calculate_dimensions(vector);
	std::reverse(dimensions.begin(), dimensions.end());
	boost::multi_array<T1, Dimensions> arr;
	arr.resize(dimensions);
	return arr;
}

template<typename T1, const int Dimensions, typename T2>
auto fill_multi_array(std::vector<T2>& vector, boost::multi_array<T1, Dimensions>& multi_arr, int dimension = 0, std::vector<int> position=std::vector<int>(Dimensions))
{

	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		position[dimension] = i;
		multi_arr(position) = vector[i];
	}
	return multi_arr;
}

template<typename T1, const int Dimensions, typename T2>
auto fill_multi_array(std::vector<std::vector<T2>>& vector, boost::multi_array<T1, Dimensions>& multi_arr, int dimension=0, std::vector<int> position=std::vector<int>(Dimensions))
{
	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		position[dimension] = i;
		fill_multi_array<T1, Dimensions>(vector[i], multi_arr, dimension+1, position);
	}
	return multi_arr;
}

int main()
{
	std::vector<std::vector<int>> vector{ {1,2,3}, {4,5,6}, {7,8,9} };

	auto multi_arr = create_multi_array<int, 2>(vector);
	fill_multi_array<int, 2>(vector, multi_arr);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << multi_arr[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}