#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int left, int middle, int right) // middle - boundary between two arrays to merge
{
	int current_1 = left, current_2 = middle;
	while (current_1 < current_2 && current_2 < right)
	{
		if (arr[current_2] < arr[current_1])
		{
			for (int i = middle; i > current_1; i--) swap(arr[i], arr[i - 1]);
			middle++;
			current_2++;
		}
		else current_1++;
	}
}

void merge_sort(vector<int>& arr, int left, int right) // left and right - boundaries of part of array to sort
{
	if (right - left < 2) return;
	int middle = (left + right) / 2;
	merge_sort(arr, left, middle);
	merge_sort(arr, middle, right);
	merge(arr, left, middle, right);
}

int main()
{
	cout << "Put your array here (put any symbol is not a digit to finish):" << endl;
	vector<int> arr(1);

	int i = 0;
	while (cin >> arr[i])
	{
		arr.push_back(0);
		i++;
	}
	arr.pop_back();

	merge_sort(arr, 0, arr.size());

	for (auto elem : arr) cout << elem << '\t';

	return 0;
}