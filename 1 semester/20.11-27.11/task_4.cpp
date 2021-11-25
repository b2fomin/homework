#include<iostream>
#include<chrono>

constexpr bool is_prime(int n)
{
	for (int d = 2; d <= n / 2; ++d)
	{
		if (n % d == 0)
		{
			return false;
		}
	}

	return n > 1;
}

constexpr int nth_prime(int n)
{
	if (n == 1) return 2;
	const int k = nth_prime(n - 1);
	for (int i = k + 1; i < k * k; ++i)
	{
		if (is_prime(i)) return i;
	}
}

int main()
{
	std::cout << nth_prime(1000);
	return 0;
}