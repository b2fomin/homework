#include<boost/multi_index_container.hpp>
#include<boost/multi_index/member.hpp>
#include<boost/multi_index/hashed_index.hpp>
#include<boost/multi_index/ordered_index.hpp>
#include<boost/multi_index/random_access_index.hpp>
#include<iostream>

using namespace boost::multi_index;

struct Phone_Owner
{
	std::string surname;
	std::string name;
	std::string patronymic;
	std::string number;
};

using phone_owner_multi_index = multi_index_container<
	Phone_Owner, indexed_by<
	ordered_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::surname> >,
	hashed_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::surname> >,
	hashed_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::name> >,
	hashed_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::patronymic> >,
	hashed_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::number> >,
	random_access<>,
	ordered_non_unique<
	member<Phone_Owner, std::string, &Phone_Owner::surname> > > >;

int main()
{
	setlocale(LC_ALL, "Rus");

	phone_owner_multi_index phone_owners;

	phone_owners.insert({ "Капустина", "Галина", "Николаевна", "670-01-39" });
	phone_owners.insert({ "Качанов", "Владимир", "Николаевич","670-03-06" });
	phone_owners.insert({ "Качанов", "Иван", "Михайлович", "670-04-56" });
	phone_owners.insert({ "Тувин", "Даниил", "Александрович", "670-05-43" });

	auto& surnames = phone_owners.get<1>();
	std::cout << surnames.count("Качанов") << std::endl << std::endl;

	auto iterator = surnames.find("Тувин");
	surnames.modify(iterator, [](Phone_Owner& phone_owner) { phone_owner.surname = "Иванов"; });


	for (auto& elem : phone_owners)
		std::cout << elem.surname << " " << elem.name << " " << elem.patronymic << " " << elem.number << std::endl;
	std::cout << std::endl;

	auto& random_phone_owner = phone_owners.get<5>()[0];
	std::cout << random_phone_owner.surname << " " << random_phone_owner.name << " " <<
		random_phone_owner.patronymic << " " << random_phone_owner.number << std::endl;

	return 0;
}