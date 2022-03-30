#include<iostream>
#include<future>
#include<thread>
#include<algorithm>
#include<vector>
#include<iomanip>

double integrate(double (*func)(double), double a, double b, double eps = pow(10, -6))
{
	double res{ 0 };
	for (double value = a; value <= b; value += eps)
	{
		res += func(value) * eps;
	}

	return res;
}

double parallel_integrate(double (*func)(double), double a, double b, double eps = pow(10, -6))
{
	const std::size_t max_threads = (int)((b - a + eps) / eps);
	const std::size_t hardware_threads = std::thread::hardware_concurrency();
	const std::size_t num_threads = std::min(hardware_threads == 0 ? 2 : hardware_threads, max_threads);

	std::vector<std::future<double>> futures(num_threads - 1);
	double left = a, right = a + (b - a) / num_threads;

	for (int i = 0; i < num_threads - 1; ++i)
	{
		futures[i] = std::async(integrate, func, left, right, eps);

		left += (b - a) / num_threads;
		right += (b - a) / num_threads;
	}

	auto result = integrate(func, left, right, eps);

	for (auto& future : futures)
	{
		result += future.get();
	}

	return result;
}

int main()
{
	auto func = [](double x) {return sqrt(1 - x * x); };

	auto pi = 2 * parallel_integrate(func, -1, 1,);

	std::cout << std::setprecision(10) << pi << std::endl;

	return 0;
}