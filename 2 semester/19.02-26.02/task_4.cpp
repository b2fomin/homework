#include<boost/multi_index_container.hpp>
#include<boost/multi_index/member.hpp>
#include<boost/multi_index/hashed_index.hpp>
#include<boost/multi_index/ordered_index.hpp>
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
		member<Phone_Owner, std::string, &Phone_Owner::number> > > >;

int main()
{
	setlocale(LC_ALL, "Rus");

	phone_owner_multi_index phone_owners;

	phone_owners.insert({ "Капустина", "Галина", "Николаевна", "670-01-39" });
	phone_owners.insert({ "Качанов", "Владимир", "Николаевич","670-03-06" });
	phone_owners.insert({"Качанов", "Иван", "Михайлович", "670-04-56"});
	phone_owners.insert({"Тувин", "Даниил", "Александрович", "670-05-43"});

	return 0;
}