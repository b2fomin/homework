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
	

	return 0;
}