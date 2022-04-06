#include<iostream>
#include<thread>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<random>
#include<mutex>
#include<functional>

void points_under_function(double (*func)(double), double a, double b, double min, double max, int N, int& result)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> x_distribution(a, b);
	std::uniform_real_distribution<double> y_distrbution(min, max);
	std::mutex mutex;

	for (int i = 0; i < N; ++i)
	{
		auto x = x_distribution(gen);
		auto y = y_distrbution(gen);
		std::lock_guard<std::mutex> lock(mutex);
		if (y <= func(x)) ++result;
	}
}

double parallel_integrate(double (*func)(double), double a, double b, double min, double max, int N)
{
	const std::size_t max_threads = N;
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(hardware_threads == 0 ? 2 : hardware_threads, max_threads);

	std::vector<std::thread> threads(num_threads - 1);
	double block_size = (b - a) / num_threads;
	double left = a, right = a + block_size;
	int K = 0;

	for (int i = 0; i < num_threads - 1; ++i)
	{
		threads[i] = std::thread(points_under_function, func, left, right, min, max, N / num_threads, std::ref(K));

		left += block_size;
		right += block_size;
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	points_under_function(func, left, right, min, max, N / num_threads, K);

	return (max - min) * (b - a) * K / N;
}

int main()
{
	auto func = [](double x) {return sqrt(1 - x * x); };

	auto pi = 2 * parallel_integrate(func, -1, 1, 0, 1, pow(10, 6));

	std::cout << std::setprecision(5) << pi << std::endl;

	return 0;
}