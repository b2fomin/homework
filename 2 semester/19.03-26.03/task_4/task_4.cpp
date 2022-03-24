#include<iostream>
#include<vector>
#include<filesystem>
#include<fstream>

#include"json.hpp"

struct Human
{
	std::size_t age;
	std::string name;
	std::string surname;
	bool happy;

	friend std::istream& operator>>(std::istream&, Human&);
};

std::istream& operator>> (std::istream& in, Human& human)
{
	in >> human.age >> human.name >> human.surname >> human.happy;
	return in;
}

int main()
{
	std::vector<Human> humans;
	Human human;
	while (std::cin >> std::boolalpha >> human) humans.push_back(human);

	std::vector<nlohmann::json> jsons;

	for (auto& elem : humans)
	{
		nlohmann::json j;
		j["age"] = elem.age;
		j["name"] = elem.name;
		j["surname"] = elem.surname;
		j["happy"] = elem.happy;
		jsons.push_back(j);
	}
	std::filesystem::remove_all(std::filesystem::current_path() / "task_4" / "JSON");
	std::filesystem::create_directory(std::filesystem::current_path() / "task_4" / "JSON");

	for (std::size_t i = 0; i < jsons.size(); ++i)
	{
		std::fstream("./task_4/JSON/file_" + std::to_string(i) + ".txt", std::ios_base::out) << jsons[i];
	}

	return 0;
}