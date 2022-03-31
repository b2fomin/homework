#include<algorithm>
#include<execution>
#include<iostream>
#include<vector>
#include"Stopwatch.hpp"

int main()
{
	Stopwatch mywatch;
	std::vector<int> data(pow(10, 6));
	for (int i = 0; i < data.size(); ++i) data[i] = i;

	auto func = [](int& elem) {return elem * elem; };

	mywatch.start();
	std::for_each(std::execution::par, data.begin(), data.end(), func);
	mywatch.stop();
	std::cout << "parallel_for_each: " << mywatch.time() << std::endl;
	mywatch.reset();

	mywatch.start();
	std::for_each(std::execution::seq, data.begin(), data.end(), func);
	mywatch.stop();
	std::cout << "not_parallel_for_each: " << mywatch.time() << std::endl;
	mywatch.reset();

	std::cout << std::endl;

	mywatch.start();
	std::sort(std::execution::par, data.begin(), data.end());
	mywatch.stop();
	std::cout << "parallel_sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	mywatch.start();
	std::sort(std::execution::seq, data.begin(), data.end());
	mywatch.stop();
	std::cout << "not_parallel_sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	return 0;
}