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

template<class T, std::size_t N>
void merge_sort(T(&array)[N], std::function<bool(T, T)> comparator = nullptr, int left = 0, int right = N) // left and right - boundaries of part of array to sort
{
	if (comparator == nullptr) comparator = [](T n1, T n2) {return n1 << n2; };
	if (right - left < 2) return;
	int middle = (left + right) / 2;
	merge_sort(array, comparator, left, middle);
	merge_sort(array, comparator, middle, right);
	merge(array, left, middle, right, comparator);
}