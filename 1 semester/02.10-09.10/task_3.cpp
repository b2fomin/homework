#include<iostream>
#include<string>
#include<vector>

class Animal
{
	double weight;
	std::string name;
	static const std::vector<std::string> permissions_name;
	static const std::vector<std::string> permissions_weight;
public:
	Animal(double weight, std::string name) :weight(weight), name(name) {};

	std::string& access_name(std::string function)
	{
		for (auto& elem : permissions_name)
		{
			if (elem == function) return name;
		}
		throw "No access";
	}

	double& access_weight(std::string function)
	{
		for (auto& elem : permissions_name)
		{
			if (elem == function) return weight;
		}
		throw "No access";
	}

};

const std::vector<std::string> Animal::permissions_name{ "feed" };
const std::vector<std::string> Animal::permissions_weight{ "feed" };

void feed(Animal pet)
{
	auto pet_name = pet.access_name("feed");
	std::cout << "Feeding " << pet_name;
	auto pet_weight = pet.access_weight("feed");
	pet_weight++;
}

int main()
{
	Animal cat(10,"Kitty");
	feed(cat);
}