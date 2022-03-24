#include<iostream>
#include<filesystem>
#include<string>

int main()
{
	system("chcp 1251");
	std::cout << "Enter the path: "<<std::endl;
	std::filesystem::path path;
	std::cin >> path;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const& entry : std::filesystem::directory_iterator(path))
		{
			std::cout << "File's name: " << entry.path().filename().string() << std::endl;

			if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
			{
				std::cout << "File's size: " << std::filesystem::file_size(entry) << std::endl;
			}

			std::cout << "File's last write time: " << std::chrono::duration_cast<std::chrono::seconds>(std::filesystem::last_write_time(entry).time_since_epoch()).count()<<std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}