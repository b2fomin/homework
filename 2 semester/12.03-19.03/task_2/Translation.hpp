#pragma once
#include<boost/multi_index_container.hpp>
#include<boost/multi_index/member.hpp>
#include<boost/multi_index/hashed_index.hpp>
#include<string>


class Translator
{
private:
	struct Symbol
	{
		std::string �yrillic;
		std::string latin;
	};

	using symbol_multi_index =boost::multi_index::multi_index_container <
		Symbol, boost::multi_index::indexed_by <
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, std::string, &Symbol::�yrillic > >,
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, std::string, &Symbol::latin > > > >;

	static symbol_multi_index symbol_arr;

	Translator();

	static void fill_symbol_arr();

public:
	static void translate_from_rus_into_en(std::string&);
	static void translate_from_en_into_rus(std::string&);
};