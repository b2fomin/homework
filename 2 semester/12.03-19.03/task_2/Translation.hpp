#pragma once
#include<boost/multi_index_container.hpp>
#include<boost/multi_index/member.hpp>
#include<boost/multi_index/hashed_index.hpp>


class Translator
{
private:
	static struct Symbol
	{
		const std::string ñyrillic;
		const std::string latin;
	};

	using symbol_multi_index = boost::multi_index_container <
		Symbol, boost::multi_index::indexed_by <
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, const std::string, &Symbol::ñyrillic > >,
		boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Symbol, const std::string, &Symbol::latin > > > >;

	static symbol_multi_index symbol_arr;

	Translator();

	void fill_symbol_arr();

public:
	void translate_from_rus_into_en(std::string&);
	void translate_from_en_into_rus(std::string&);
};