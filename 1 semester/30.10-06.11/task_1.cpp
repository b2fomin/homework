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
	if (comparator == nullptr) comparator = [](T n1, T n2) {return n1 < n2; };
	if (right - left < 2) return;
	int middle = (left + right) / 2;
	merge_sort(array, comparator, left, middle);
	merge_sort(array, comparator, middle, right);
	merge(array, left, middle, right, comparator);
}

template<class T>
void merge(T* array, int size, int left, int middle, int right, std::function<bool(T, T)> comparator)
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

template<class T>
void merge_sort(T* array, std::size_t size, std::function<bool(T, T)> comparator = nullptr, int left = 0, int right=-1) // left and right - boundaries of part of array to sort
{
	if (comparator == nullptr) comparator = [](T n1, T n2) {return n1 < n2; };
	if (right == -1) right = size;
	if (right - left < 2) return;
	int middle = (left + right) / 2;
	merge_sort(array, size, comparator, left, middle);
	merge_sort(array, size, comparator, middle, right);
	merge(array, size, left, middle, right, comparator);
}

int main()
{
	int* arr = new int[5]{5,3,4,2,1};
	merge_sort(arr, 5);
	for (int i = 0; i < 5;++i) std::cout << arr[i] << '\t';
	delete[] arr;
	std::cout << std::endl;
	int arr1[5]{ 5,3,4,2,1 };
	merge_sort(arr1);
	for (int i = 0; i < 5; ++i) std::cout << arr1[i] << '\t';
	return 0;
}