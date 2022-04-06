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

	return pi;
}