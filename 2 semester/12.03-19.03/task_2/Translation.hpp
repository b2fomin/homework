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
		std::u32string ñyrillic;
		std::u32string latin;
	};

	using symbol_multi_index =boost::multi_index::multi_index_container <
		Symbol, boost::multi_index::indexed_by <
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, std::u32string, &Symbol::latin > >,
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, std::u32string, &Symbol::ñyrillic > > > >;

	static symbol_multi_index symbol_arr;

	Translator();

	static void fill_symbol_arr();

public:
	static void translate_from_rus_into_en(std::u32string&);
	static void translate_from_en_into_rus(std::u32string&);
};