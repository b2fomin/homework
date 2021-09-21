#include <iostream>
#include <vector>

using namespace std;

void switch_numbers(int& a, int& b)
{
	a += b;
	b = a - b;
	a -= b;
}

void merge(vector<int>& arr, int left, int middle, int right)
{
	int current_1 = left, current_2 = middle;
	while (current_1 < current_2 && current_2 < right )
	{
		if (arr[current_2] < arr[current_1])
		{
			for (int i = middle; i > current_1; i--) switch_numbers(arr[i], arr[i - 1]);
			middle++;
			current_2++;
		}
		else current_1++;
	}
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


	for (int i = 0; i < arr.size(); i++) cout << arr[i] << '\t';

	return 0;
}