#include<fstream>
#include<iostream>
#include<random>
#include<string>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::fstream file("./task_2/task_2.txt", std::ios_base::out);
	file.imbue(std::locale("ru_RU.UTF-8"));
	std::size_t size_of_line = 10;
	std::size_t number_of_lines = 200;
	for (auto i = 0; i < number_of_lines; ++i)
	{
		for (auto i = 0; i < size_of_line; ++i)
		{
			file << gen() % 10;
		}
		file << std::endl;
	}

	return 0;
}