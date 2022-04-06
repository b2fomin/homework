#include<iostream>
#include<vector>

std::vector<int> prefix_function(const std::string& s)
{
	std::vector<int> pi(s.size(), 0);

	for (int i = 1; i < pi.size(); ++i)
	{
		int j = pi[i - 1];

		while (j != 0 && s[j] != s[i]) j = pi[j - 1];
		if (s[i] == s[j]) ++j;

		pi[i] = j;
	}

	return std::move(pi);
}

std::vector<int> find(const std::string& sample, const std::string& text, const char delimeter='#')
{
	int length = sample.size();
	std::string str_for_search = sample +delimeter + text;
	auto pi = prefix_function(str_for_search);
	std::vector<int> index;
	for (int i=2*length;i<pi.size();++i)
	{
		if (pi[i] == length) index.push_back(i - 2 * length);
	}

	return index;
}