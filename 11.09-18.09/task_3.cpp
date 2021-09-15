#include <iostream>
#include <vector>
#include <iomanip>

bool bin_search(std::vector<int>& arr, int& value)
{
	int left = 0, right = arr.size(), current = 0;
	while (right - left > 1)
	{
		current = (left + right) / 2;
		if (arr[current] > value) right = current;
		else left = current;
	}
	if (arr[left] == value || arr[right] == value) return true;
	return false;
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
	cout << "Enter number you want to find: ";
	int value;
	cin >> value;
	cout << boolalpha << bin_search(arr, value);

	return 0;

}