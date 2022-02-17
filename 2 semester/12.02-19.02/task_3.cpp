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

