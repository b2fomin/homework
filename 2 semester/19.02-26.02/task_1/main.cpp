#include<iostream>
#include"Stopwatch.hpp"
#include<vector>
#include<set>

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

	std::cout << "Set time is " << mywatch.time() << std::endl;
	mywatch.reset();

	return 0;
}