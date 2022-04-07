#include"priority_queue.hpp"
#include<iostream>
#include<iomanip>

int main()
{
	Priority_queue<int> queue;
	queue.push(42);
	std::cout << queue.top() << std::endl;
	queue.wait_and_pop();
	std::cout << std::boolalpha << queue.try_pop() << std::endl;
}