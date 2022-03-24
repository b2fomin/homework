#include<iostream>
#include<vector>

#include"json.hpp"

struct Human
{
	std::size_t age;
	std::string name;
	std::string surname;
	std::vector<std::string> card_id;

	friend std::istream& operator>>(std::istream&, Human&);
};

std::istream& operator>> (std::istream& in, Human& human)
{
	in >> human.age >> human.name >> human.surname;
	std::string id;
	while (in >> id) human.card_id.push_back(id);
}

int main()
{
	std::vector<Human> humans;
	Human human;
	while (std::cin >> human) humans.push_back(human);

	std::vector<nlohmann::json> jsons;

	for (auto& elem : humans)
	{
		nlohmann::json j;
		j["age"] = elem.age;
		j["name"] = elem.name;
		j["surname"] = elem.surname;
		j["card_id"] = elem.card_id;
		jsons.push_back(j);
	}

	return 0;
}