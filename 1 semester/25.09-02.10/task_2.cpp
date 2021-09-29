#include<iostream>
#include<string>
#include<vector>

struct Student;

struct Lesson
{
	std::string name;
	std::vector<Student*> students;

	Lesson(std::string name) : name(name)
	{

	}

	friend std::ostream& operator<<(std::ostream& out, const Lesson& lesson);
};

std::ostream& operator<<(std::ostream& out, const Lesson& lesson)
{
	return out << lesson.name;
}

struct Student
{
	std::string name;
	std::vector<Lesson*> lessons;

	Student(std::string name) :name(name)
	{

	}

	friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

std::ostream& operator<<(std::ostream& out, const Student& student)
{
	return out << student.name;
}

template<typename T>
void print(std::vector<T> arr)
{
	for (auto elem : arr) std::cout << *elem << '\t';
	std::cout << std::endl;
}

int main()
{
	std::vector<Lesson> Lessons
	{
		Lesson("physics"),
		Lesson("chemistry"),
		Lesson("math")
	};

	std::vector<Student> Students
	{
		Student("Bob"),
		Student("Steve"),
		Student("James")
	};

	for (auto& elem : Lessons)
	{
		static int i = 0;
		elem.students.push_back(&Students[i < Students.size() ? i : 0]);
		elem.students.push_back(&Students[++i < Students.size() ? i : 0]);
	}

	for (auto& elem : Students)
	{
		static int i = 0;
		elem.lessons.push_back(&Lessons[i < Students.size() ? i : 0]);
		elem.lessons.push_back(&Lessons[++i < Students.size() ? i : 0]);
	}

	for (auto& elem : Students) print(elem.lessons);
	std::cout << std::endl;
	for (auto& elem : Lessons) print(elem.students);
	std::cout << std::endl;
}


