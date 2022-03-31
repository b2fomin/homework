#include<iostream>
#include<algorithm>
#include<thread>
#include<future>
#include<vector>
#include<execution>

template<typename Iterator, typename Func>
Func parallel_for_each(Iterator first, Iterator last, Func func)
{
	const std::size_t length = std::distance(first, last);
	const std::size_t min_per_thread = 25;
	const std::size_t max_threads = (length + min_per_thread - 1) / min_per_thread;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	if (num_threads <= 2) return std::for_each(first, last, func);

	Iterator middle = first;
	std::advance(middle, length / 2);
	std::future<void> first_half_result = std::async(
		[](auto first, auto last, auto func) {parallel_for_each(first, last, func); }, first, middle, func);

	parallel_for_each(middle, last, func);
	first_half_result.get();

	return func;
}

int main()
{
	std::vector<long long int> data(pow(10, 5));
	for (std::size_t i = 0; i < data.size(); ++i) data[i] = i;

	auto func = [](auto& elem) { elem=elem*elem; };

	parallel_for_each(data.begin(), data.end(), func);

	return 0;
}