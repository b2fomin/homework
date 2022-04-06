#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<algorithm>
#include<functional>

std::vector<int> prefix_function(const std::string& s)
{
	std::vector<int> pi(s.size(), 0);

	for (int i = 1; i < pi.size(); ++i)
	{
		int j = pi[i - 1];

		while (j != 0 && s[j] != s[i]) j = pi[j - 1];
		if (s[i] == s[j]) ++j;

		pi[i] = j;
	}

	return pi;
}

void find(const std::string& sample, const std::string& text, std::vector<int>& index, const char delimeter='#')
{
	std::mutex mutex;
	int length = sample.size();
	std::string str_for_search = sample +delimeter + text;
	auto pi = prefix_function(str_for_search);
	std::vector<int> index;
	for (int i=2*length;i<pi.size();++i)
	{
		if (pi[i] == length)
		{
			std::lock_guard<std::mutex> lock(mutex);
			index.push_back(i - 2 * length);
		}
	}
}

std::vector<int> parallel_find(const std::string& sample, const std::string& text, const char delimeter = '#')
{
	const std::size_t max_threads = (text.size() + sample.size() - 1) / sample.size();
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	std::vector<std::thread> threads(num_threads - 1);
	std::size_t block_size = text.size() / num_threads;
	auto left = text.begin(), right=left;
	std::advance(right, block_size);
	std::vector<int> index;

	for (int i = 0; i < threads.size(); ++i)
	{
		std::string string;
		std::copy(left, right, string);
		threads[i] = std::thread(find, sample, string, index, delimeter);

		std::advance(left, block_size);
		std::advance(right, block_size);
	}

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	std::string string;
	std::copy(left, right, string);
	find(sample, string, index, delimeter);

	std::sort(index.begin(), index.end());
	return index;
}