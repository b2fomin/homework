#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<algorithm>
#include<functional>

std::vector<int> prefix_function(const std::string& s)
{
	std::vector<int> pi(s.size());

	for (int i = 1; i < pi.size(); ++i)
	{
		int j = pi[i - 1];

		while (j != 0 && s[j] != s[i]) j = pi[j - 1];
		if (s[i] == s[j]) ++j;

		pi[i] = j;
	}

	return pi;
}

void find(const std::string& text, const std::string& sample, std::vector<int>& index, std::size_t shift = 0, const char delimeter = '#')
{
	std::mutex mutex;
	int length = sample.size();
	std::string str_for_search = sample + delimeter + text;
	auto pi = prefix_function(str_for_search);
	for (int i = 2 * length; i < pi.size(); ++i)
	{
		if (pi[i] == length)
		{
			std::lock_guard<std::mutex> lock(mutex);
			index.push_back(i - 2 * length + shift);
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
	auto begin=text.begin(), left = begin, right = left;
	std::advance(right, block_size);
	std::vector<int> index;

	for (int i = 0; i < threads.size(); ++i)
	{
		std::string string;
		for (auto iter = left; iter != right; ++iter) string += *iter;

		threads[i] = std::thread(find, string, sample, std::ref(index), std::distance(begin, left), delimeter);

		std::advance(left, block_size);
		std::advance(right, block_size);
	}

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	std::string string;
	for (auto iter = left; iter != right; ++iter) string += *iter;

	find(string, sample, index, std::distance(begin, left), delimeter);

	std::sort(index.begin(), index.end());
	return index;
}

std::string generate_DNA(const std::size_t size)
{
	std::string letters = "AGTC";
	std::string DNA;

	for (int i = 0; i < size; ++i)
	{
		DNA.push_back(letters[std::rand() % letters.size()]);
	}

	return DNA;
}

int main()
{
	std::size_t size = pow(10, 3);
	std::string DNA = generate_DNA(size);
	std::cout << DNA << std::endl;
	std::string sample;

	std::cout << "Enter sample: ";
	std::cin >> sample;

	auto index = parallel_find(sample, DNA);
	for (auto& elem : index) std::cout << elem << std::endl;
}