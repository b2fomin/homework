#include <iostream>
#include <tuple>

using namespace std;
tuple<int*, int> lcs(int* arr1, int* arr2, int size1, int size2)
{
	int** d = new int* [size1]; // in [i][j] position is lenght of longest common subsequence for arr1's i first elements and arr2's j first elements 
	for (int i = 0; i < size1; i++) {
		d[i] = new int[size2];
		for (int j = 0; j < size2; j++) {
			d[i][j] = 0;
		}
	}

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (arr1[i] == arr2[j])
			{
				if (i == 0 || j == 0) d[i][j] = 1;
				else d[i][j] = d[i - 1][j - 1] + 1;
			}
			else
			{
				if (i == 0) d[i][j] = d[i][j - 1];
				else if (j == 0) d[i][j] = d[i - 1][j];
				else d[i][j] = max(d[i - 1][j], d[i][j - 1]);
			}
		}
	}

	int max_lenght = 0, pos = 0;
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (d[i][j] > max_lenght)
			{
				max_lenght = d[i][j];
				pos = i;
			}
		}
	}
	int* result = new int[max_lenght];
	for (int i = max_lenght - 1; i >= 0; i--) {
		for (int j = 0; j < size2; j++) {
			if (d[pos][j] == i + 1) { result[i] = arr2[j]; break; }
		}
	}

	for (int i = 0; i < size1; i++) delete[] d[i];
	delete[] d;

	return make_tuple(result, max_lenght);
}

int main()
{
	cout << "Enter sizes of arrays: ";
	int size1 = 0, size2 = 0;
	cin >> size1 >> size2;

	cout << endl << "Put 1st array here:" << endl;
	int* arr1 = new int[size1];
	for (int i = 0; i < size1; i++) cin >> arr1[i];
	cout << endl << "Put 2nd array here:" << endl;
	int* arr2 = new int[size2];
	for (int i = 0; i < size2; i++) cin >> arr2[i];

	int* result; int size;
	tie(result, size) = lcs(arr1, arr2, size1, size2);
	for (int i = 0; i < size; i++) {
		cout << result[i] << '\t';
	}

	delete[] arr1;
	delete[] arr2;
	delete[] result;
}