#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include"Stopwatch.hpp"

template < typename Iterator, typename T, typename Func >
T parallel_accumulate(Iterator first, Iterator last, T init, Func func = std::plus<T>(),
	std::size_t wanted_num_threads = std::thread::hardware_concurrency())
{
	const std::size_t length = std::distance(first, last);
	const std::size_t min_per_thread = 25;
	const std::size_t max_size = (length + min_per_thread - 1) / min_per_thread;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(std::min(hardware_threads != 0 ? hardware_threads : 2, max_size), std::min(max_size, wanted_num_threads));

	std::vector<std::future<T>> futures(num_threads - 1);
	const std::size_t block_size = length / num_threads;

	Iterator left = first;
	Iterator right = first;
	std::advance(right, block_size);

	for (int i = 0; i < futures.size(); ++i)
	{
		futures[i] = std::async(std::accumulate<Iterator, T, Func>, left, right, T(), func);

		std::advance(left, block_size);
		std::advance(right, block_size);
	}

	T result = std::accumulate(left, right, init, func);
	for (auto& future : futures)
	{
		result += future.get();
	}

	return result;
}

int main()
{
	Stopwatch mywatch;
	std::vector<long long int> data(pow(10,8));
	std::iota(data.begin(), data.end(), 2);

	for (std::size_t num_threads = 1; num_threads <= std::thread::hardware_concurrency(); ++num_threads)
	{
		mywatch.start();
		parallel_accumulate(data.begin(), data.end(), 1, std::multiplies<long long int>(), num_threads);
		mywatch.stop();
		std::cout << mywatch.time<std::chrono::microseconds>() << std::endl;
		mywatch.reset();
	}
}
/*
* ѕо графику видно, что врем€ убывает с возрастанием количества потоков. ѕри N>=2 производительность увеличиваетс€ не более чем в 1.2 раза.
  ќптимальным можно считать N=5, так как врем€ находитс€ в пределах 30-40 мс при N>=5.
*/