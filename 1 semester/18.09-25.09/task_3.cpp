#include<iostream>
#include<algorithm>
#include<vector>

void print(std::vector<int> arr)
{
	for (auto elem : arr) std::cout << elem << '\t';
	std::cout << std::endl;
}

int main()
{
	using namespace std;

	cout << "Enter size of array:" << endl;
	int size;
	cin >> size;
	cout << "Put your array here:" << endl;
	vector<int> arr(size);
	for (auto& elem:arr) { cin >> elem; }

	sort(arr.begin(), arr.end(), [](auto& x, auto& y) {return (x < y); });//ascending
	print(arr);
	sort(arr.begin(), arr.end(), [](auto& x, auto& y) {return (x > y); });//descending
	print(arr);

	return 0;
}