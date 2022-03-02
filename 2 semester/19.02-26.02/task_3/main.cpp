#include<iostream>
#include<unordered_set>
#include"Hash_functions.hpp"
#include<vector>

int main()
{
	char symbols[27] = "abcdefghijklmnopqrstuvwxyz";
	std::vector<char*> strings;

	for (int i = 0; i < 5000000; ++i)
	{
		char* string = new char[6];
		int i_copy = i;
		for (int j = 0; j < 6; ++j)
		{
			string[j] = symbols[i_copy % 27];
			i_copy /= 27;
		}

		strings.push_back(string);
	}

	for (auto& function : {RSHash, JSHash, PJWHash, ELFHash,
		BKDRHash, SDBMHash, DJBHash, DEKHash, APHash})
	{
		std::size_t collisions = 0;
		std::unordered_set<std::size_t> hashes;

		for (auto& string:strings)
		{
			auto old_size = hashes.size();
			hashes.insert(function(string, 6));

			if (old_size == hashes.size())
				++collisions;
		}

		std::cout << collisions << std::endl;
	}

	for (auto& string : strings)
		delete[] string;

	return 0;
}