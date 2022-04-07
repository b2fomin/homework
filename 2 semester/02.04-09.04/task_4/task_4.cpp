#include<boost/lockfree/stack.hpp>
#include<boost/lockfree/queue.hpp>
#include"threadsafe_stack.hpp"
#include"threadsafe_queue.hpp"
#include<vector>
#include<atomic>
#include<thread>
#include<algorithm>
#include<exception>
#include<functional>
#include"Stopwatch.hpp"
#include<iostream>

std::atomic_bool flag = false;

template<typename T>
void push(int M, T& arr)
{
	while (!flag.load());

	for (int i = 0; i < M; ++i)
	{
		arr.push(i);
	}
}

template<typename T>
void pop(int M, T& arr)
{
	while (!flag.load());

	int result;
	for (int i = 0; i < M; ++i)
	{
		arr.pop(result);
	}
}

template<typename T>
int test(int N, int M, T& arr)
{
	flag.store(false);
	Stopwatch mywatch;

	std::vector<std::thread> threads(2 * N);
	for (int i = 0; i < N; ++i) threads[i] = std::thread(push<T>, M, std::ref(arr));
	for (int i = N; i < 2 * N; ++i) threads[i] = std::thread(pop<T>, M, std::ref(arr));

	mywatch.start();
	flag = true;
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	mywatch.stop();

	return mywatch.time();
}

int main()
{
	int N = 3;
	int M = 1000;
	boost::lockfree::stack<int> boost_stack(1);
	Threadsafe_Stack<int> custom_stack;

	boost::lockfree::queue<int> boost_queue(1);
	Threadsafe_Queue<int> custom_queue;

	std::cout << "Boost stack: " << test(N, M, boost_stack) << std::endl;
	std::cout << "Custom stack: " << test(N, M, custom_stack) << std::endl;

	std::cout << "Boost queue: " << test(N, M, boost_queue) << std::endl;
	std::cout << "Custom queue: " << test(N, M, custom_queue) << std::endl;
	return 0;
}