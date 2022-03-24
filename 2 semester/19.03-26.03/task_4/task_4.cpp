#include<iostream>
#include<vector>

struct Human
{
	std::size_t age;
	std::string name;
	std::string surname;
	std::vector<std::string> card_id;

	friend std::istream& operator>>(std::istream&, Human);
};

std::istream& operator>> (std::istream& in, Human& human)
{
	in >> human.age >> human.name >> human.surname;
	std::string id;
	while (in >> id) human.card_id.push_back(id);
}

int main()
{
	return 0;
}