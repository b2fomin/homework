#include<iostream>
#include<boost/container_hash/hash.hpp>
#include<unordered_set>
#include<vector>


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

	std::size_t collisions=0;
	std::unordered_set<std::size_t> hashes;
	std::vector<int> sizes;
	for (int size = 1000; size < 2000000; size += 10000)
		sizes.push_back(size);

	for (int i = 0; i < sizes[sizes.size() - 1]; ++i)
	{
		std::string name;
		int i_copy = i;
		for (int j = 0; j < 5; ++j)
		{
			name += symbols[i_copy % 27];
			i_copy /= 27;
		}

		Student student{ i % 60, name, (float)(std::rand() % 10) / 2 };
		auto old_size = hashes.size();
		hashes.insert(hash_value(student));

		if (old_size == hashes.size())
			++collisions;

		for (auto& size : sizes)
			if (size == i)
			{
				std::cout << size << " " << collisions << std::endl;
				break;
			}
	}

	return 0;
}