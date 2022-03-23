#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>

int main()
{
	std::fstream file("algorithm.txt", std::ios_base::in);

	char ch;
	std::stringstream data;

	while (file.get(ch))
	{
		if (ch == '/')
		{
			if (file.peek() == '*')
			{
				while (!(file.get() == '*' && file.seekg(1, std::ios_base::cur).get() == '/'));
			}
			else if (file.peek() == '/')
			{
				while (file.get() != '\n');
			}
			else data << ch;
		}
		else data << ch;
	}
	file.close();

	file.open("algorithm.txt", std::ios_base::out);
	file << data.str();
	
	return 0;
}