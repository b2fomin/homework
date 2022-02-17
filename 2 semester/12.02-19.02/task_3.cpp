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
