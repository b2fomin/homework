#include <iostream>
#include <vector>

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

	return 0;
}