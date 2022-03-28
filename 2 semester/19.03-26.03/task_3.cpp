#include<iostream>
#include<filesystem>
#include<string>
#include<chrono>

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
			if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
			{
				std::string filename = entry.path().filename().string();
				auto point = filename.rfind('.');

				std::cout << "File's name: ";
				for (std::size_t i = 0; i < point; ++i) std::cout << filename[i];

				std::cout << std::endl << "File's extension: ";
				for (std::size_t i = point; i < filename.size(); ++i) std::cout << filename[i];
				std::cout << std::endl;

				std::cout << "File's size: " << std::filesystem::file_size(entry) << std::endl;
			}
			else if (std::filesystem::is_directory(path))
					std::cout << "Directory's name: " << entry.path().filename().string() << std::endl;

			
			auto time = std::chrono::system_clock::time_point{ std::filesystem::last_write_time(entry).time_since_epoch() };
			auto time_t = std::chrono::system_clock::to_time_t(time);

			std::cout << "Last write time: " << std::put_time(std::localtime(&time_t), "%Y-%m-%d %X")<<std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}