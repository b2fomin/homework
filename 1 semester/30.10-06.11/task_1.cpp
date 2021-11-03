#include<iostream>
#include<functional>

template<class T, std::size_t N>
void merge(T(&array)[N], int left, int middle, int right, std::function<bool(T, T)> comparator)
{
	int current_1 = left, current_2 = middle;
	while ((current_1 < current_2) && (current_2 < right))
	{
		if (comparator(array[current_2], array[current_1]))
		{
			for (int i = middle; i > current_1; i--) std::swap(array[i], array[i - 1]);
			middle++;
			current_2++;
		}
		else current_1++;
	}
}