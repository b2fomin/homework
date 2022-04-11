#include"priority_queue.hpp"
#include<iostream>
#include<iomanip>
#include<thread>
#include<vector>
#include<functional>

int main()
{
	Priority_queue<int> queue;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t N = hardware_threads != 0 ? hardware_threads : 2, M=pow(10, 6);

	std::vector<std::thread> threads(N);
	for (std::size_t i = 0; i < threads.size() / 2; ++i)
		threads[i] = std::thread
		(
			[&queue, M]
			{
				for (std::size_t j = 0; j < M; ++j) queue.push(j);
			}
		);
	for (std::size_t i = threads.size() / 2; i < threads.size(); ++i)
		threads[i] = std::thread
		(
			[&queue, M]
			{
				for (std::size_t j = 0; j < M; ++j) queue.wait_and_pop();
			}
		);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	std::cout << std::boolalpha << queue.empty() << std::endl;

	return 0;
}