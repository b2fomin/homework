#include <iostream>
#include <vector>

void switch_numbers(int& a, int& b)
{
	a += b;
	b = a - b;
	a -= b;
}

void sort(std::vector<int>& arr)
{
	int size = arr.size();
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] < arr[j])
			{
				for (int k = i; k > j; k--) { switch_numbers(arr[k], arr[k - 1]); }
				break;
			}
		}
	}
}

int main()
{
	using namespace std;

	cout << "Enter size of array: ";
	int size;
	cin >> size;
	cout << endl << "Put your array here" << endl;
	vector<int> arr;
	arr.resize(size);
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
	sort(arr);
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << '\t';
	}

	return 0;
}