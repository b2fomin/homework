#include<iostream>
#include<unordered_set>
#include"Hash_functions.hpp"


int main()
{
	char symbols[27] = "abcdefghijklmnopqrstuvwxyz";

	for (auto& function : {RSHash, JSHash, PJWHash, ELFHash,
		BKDRHash, SDBMHash, DJBHash, DEKHash, APHash})
	{
		std::size_t collisions = 0;
		std::unordered_set<std::size_t> hashes;

		for (int i = 0; i < 326797; ++i)
		{
			char* string=new char[6];
			for (int j = 0; j < 6; ++j)
			{
				string[j] = symbols[std::rand() % 26];
			}

			auto old_size = hashes.size();
			hashes.insert(function(string, 6));

			if (old_size == hashes.size())
				++collisions;
			
			delete[] string;
		}

		std::cout << collisions << std::endl;
	}

	return 0;
}