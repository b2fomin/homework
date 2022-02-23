#include<iostream>
#include"Stopwatch.hpp"
#include<algorithm>
#include<vector>
#include<deque>
#include<array>
#include<list>
#include<forward_list>

int main()
{
	//////////////////////////////////////////////////////
	const int size = 80001;
	std::vector<int> vector1;
	for (int i = size-1; i > -1; --i) vector1.push_back(i);

	std::array<int, size> array1;
	for (int i = 0; i < size; ++i) array1[i] = size-i;

	std::deque<int> deque1;
	for (int i = size-1; i > -1; --i) deque1.push_back(i);

	std::list<int> list1;
	for (int i = size-1; i > -1; --i) list1.push_back(i);

	std::forward_list<int> forward_list1;
	for (int i = 0; i < size; ++i) forward_list1.push_front(i);

	/////////////////////////////////////////////////////////////
	
	Stopwatch mywatch;
	mywatch.start();
	std::sort(vector1.begin(),vector1.end());
	std::cout << "vector std::sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	mywatch.start();
	std::sort(array1.begin(), array1.end());
	std::cout << "array std::sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	mywatch.start();
	std::sort(deque1.begin(), deque1.end());
	std::cout << "deque std::sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	mywatch.start();
	list1.sort();
	std::cout << "list own sort: " << mywatch.time()<<std::endl;
	mywatch.reset();

	mywatch.start();
	forward_list1.sort();
	std::cout << "forward_list own sort: " << mywatch.time() << std::endl;
	mywatch.reset();

	return 0;
}