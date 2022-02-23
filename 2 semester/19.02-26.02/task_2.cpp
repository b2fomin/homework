#include<iostream>
#include<boost/multi_index_container.hpp>
#include<boost/multi_index/hashed_index.hpp>
#include<boost/multi_index/member.hpp>

using namespace boost::multi_index;

struct Student
{
	int age;
	std::string name;
	float average_mark;
	std::string* department;
};

using student_multi_index = multi_index_container <
	Student, indexed_by <
	hashed_non_unique <
	member < Student, int, &Student::age> >,
	hashed_non_unique <
	member < Student, std::string, &Student::name > >,
	hashed_non_unique <
	member < Student, float, &Student::average_mark > >,
	hashed_non_unique <
	member < Student, std::string*, &Student::department > > > >;

int main()
{

	return 0;
}