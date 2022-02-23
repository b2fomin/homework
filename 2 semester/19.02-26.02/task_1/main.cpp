#include<iostream>
#include"Stopwatch.hpp"
#include<vector>
#include<set>
#include<algorithm>

int main()
{
	std::set<int> set;
	std::vector<int> vector;
	Stopwatch mywatch;

	mywatch.start();
	for (int i = 0; i < 100000; ++i)
	{
		set.insert(std::rand());
	}

	mywatch.stop();
	std::cout << "Set's time is " << mywatch.time() << std::endl;
	mywatch.reset();

	for (auto& elem : set)
	{
		vector.push_back(elem);
	}

	mywatch.start();
	std::sort(vector.begin(), vector.end());

	mywatch.stop();
	std::cout << "Vector's time is " << mywatch.time() << std::endl;


	return 0;
}