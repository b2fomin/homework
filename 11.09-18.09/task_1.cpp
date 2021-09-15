#include <iostream>
#include <string>
#include <vector>

const char punctuation[8] = { '!',':',',','.',';','?','(',')' }; // if you need to support more punctuation marks, put it here

template<typename T>
bool is_found(const T* arr, int size, T elem)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == elem) return true;
	}
	return false;
}

int main()
{
	using namespace std;

	cout << "Enter text:" << endl;
	string text;
	getline(cin, text);
	int len = text.length();
	vector<string> split_text;
	string current = "";

	for (int i = 0; i < len; i++)
	{

		if (!is_found(punctuation, 8, text[i]) && text[i] != ' ')
		{
			current += text[i];
			continue;
		}

		if (current != "") split_text.push_back(current);
		text[i] != ' ' ? current = text[i] : current = "";
	}
	split_text.push_back(current);

	for (int i = 0; i < split_text.size(); i++) {
		cout << "\"" << split_text[i] << "\"" << "\t";
	}

	return 0;
}