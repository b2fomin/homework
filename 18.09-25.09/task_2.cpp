#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout << "Put your array here (put any symbol is not a digit to finish):" << endl;
	vector<int> arr(1);

	int i = 0;
	while (cin>>arr[i])
	{
		arr.push_back(0);
		i++;
	}
	arr.pop_back();

	for (int i = 0; i < arr.size(); i++) cout << arr[i]<<'\t';

	return 0;
}