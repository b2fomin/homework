#include<iostream>
#include<algorithm>
#include<thread>
#include<future>
#include<vector>
#include<memory>

template<typename Iterator, typename Func>
Func parallel_for_each(Iterator first, Iterator last, Func func)
{
	const std::size_t length = std::distance(first, last);
	const std::size_t min_per_thread = 25;
	const std::size_t max_size = (length + min_per_thread - 1) / min_per_thread;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_size);
	std::vector<std::future<void>> futures(num_threads - 1);

	std::size_t block_size = length / num_threads;
	auto left = first;
	auto right = first;
	std::advance(right, block_size);

	for (auto& future : futures)
	{
		future = std::async([](auto left, auto right, auto func) {std::for_each(left, right, func); }, left, right, func);

		std::advance(left, block_size);
		std::advance(right, block_size);
	}

	std::for_each(left, right, func);

	for (auto& future : futures)
	{
		future.get();
	}

	return func;
}

int main()
{
	std::vector<int> data(10);
	std::fill(data.begin(), data.end(), 2);

	auto func = [](int elem) { std::cout << elem*elem << " "; };

	parallel_for_each(data.begin(), data.end(), func);

	return 0;
}