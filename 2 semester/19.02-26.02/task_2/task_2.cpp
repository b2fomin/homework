#include<iostream>
#include<boost/container_hash/hash.hpp>
#include<unordered_set>


struct Student
{
	int age;
	std::string name;
	float average_mark;
	friend std::size_t hash_value (const Student& stud)
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, stud.age);
		boost::hash_combine(seed, stud.name);
		boost::hash_combine(seed, stud.average_mark);

		return seed;
	}
};


int main()
{
	char symbols[27] = "abcdefghijklmnopqrstuvwxyz";

	for (int size = 1000; size < 200000; size += 10000)
	{
		std::size_t collisions=0;
		std::unordered_set<std::size_t> hashes;

		for (int i = 0; i < size; ++i)
		{
			std::string name;
			for (int j = 0; j < 3; ++j)
			{
				name += symbols[std::rand() % 26];
			}

			Student student{ i % 60, name, (float)(std::rand() % 10) / 2 };
			auto old_size = hashes.size();
			hashes.insert(hash_value(student));
			
			if (old_size == hashes.size())
				++collisions;
		}

		std::cout << size << " " << collisions << std::endl;
	}

	return 0;
}