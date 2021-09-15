#include <iostream>

using namespace std;
int main()
{
	cout << "Enter sizes of arrays: ";
	int size1 = 0, size2 = 0;
	cin >> size1 >> size2;
	
	cout << endl << "Put 1st array here:" << endl;
	int* arr1 = new int[size1];
	cout << endl << "Put 2nd array here:" << endl;
	int* arr2 = new int[size2];
}