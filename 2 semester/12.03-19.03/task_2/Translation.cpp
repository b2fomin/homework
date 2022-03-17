#include"Translation.hpp"

Translator::symbol_multi_index Translator::symbol_arr{};

Translator::Translator()=default;

void Translator::fill_symbol_arr()
{
	symbol_arr.insert({ U"�", U"a"});
	symbol_arr.insert({ U"�", U"b" });
	symbol_arr.insert({ U"�", U"v" });
	symbol_arr.insert({ U"�", U"g" });
	symbol_arr.insert({ U"�", U"d" });
	symbol_arr.insert({ U"�", U"e" });
	symbol_arr.insert({ U"�", U"zh" });
	symbol_arr.insert({ U"�", U"z" });
	symbol_arr.insert({ U"�", U"i" });
	symbol_arr.insert({ U"�", U"y" });
	symbol_arr.insert({ U"�", U"k" });
	symbol_arr.insert({ U"�", U"l" });
	symbol_arr.insert({ U"�", U"m" });
	symbol_arr.insert({ U"�", U"n" });
	symbol_arr.insert({ U"�", U"o" });
	symbol_arr.insert({ U"�", U"p" });
	symbol_arr.insert({ U"�", U"r" });
	symbol_arr.insert({ U"�", U"s" });
	symbol_arr.insert({ U"�", U"t" });
	symbol_arr.insert({ U"�", U"u" });
	symbol_arr.insert({ U"�", U"f" });
	symbol_arr.insert({ U"�", U"kh" });
	symbol_arr.insert({ U"�", U"ts" });
	symbol_arr.insert({ U"�", U"ch" });
	symbol_arr.insert({ U"�", U"sh" });
	symbol_arr.insert({ U"�", U"shch" });
	symbol_arr.insert({ U"�", U"\"" });
	symbol_arr.insert({ U"�", U"y" });
	symbol_arr.insert({ U"�", U"\'" });
	symbol_arr.insert({ U"�", U"e" });
	symbol_arr.insert({ U"�", U"yu" });
	symbol_arr.insert({ U"�", U"ya" });
	symbol_arr.insert({ U"�", U"A" });
	symbol_arr.insert({ U"�", U"B" });
	symbol_arr.insert({ U"�", U"V" });
	symbol_arr.insert({ U"�", U"G" });
	symbol_arr.insert({ U"�", U"D" });
	symbol_arr.insert({ U"�", U"E" });
	symbol_arr.insert({ U"�", U"Zh" });
	symbol_arr.insert({ U"�", U"Z" });
	symbol_arr.insert({ U"�", U"I" });
	symbol_arr.insert({ U"�", U"Y" });
	symbol_arr.insert({ U"�", U"K" });
	symbol_arr.insert({ U"�", U"L" });
	symbol_arr.insert({ U"�", U"M" });
	symbol_arr.insert({ U"�", U"N" });
	symbol_arr.insert({ U"�", U"O" });
	symbol_arr.insert({ U"�", U"P" });
	symbol_arr.insert({ U"�", U"R" });
	symbol_arr.insert({ U"�", U"S" });
	symbol_arr.insert({ U"�", U"T" });
	symbol_arr.insert({ U"�", U"U" });
	symbol_arr.insert({ U"�", U"F" });
	symbol_arr.insert({ U"�", U"Kh" });
	symbol_arr.insert({ U"�", U"Ys" });
	symbol_arr.insert({ U"�", U"Ch" });
	symbol_arr.insert({ U"�", U"Sh" });
	symbol_arr.insert({ U"�", U"Shch" });
	symbol_arr.insert({ U"�", U"\"" });
	symbol_arr.insert({ U"�", U"Y" });
	symbol_arr.insert({ U"�", U"\'" });
	symbol_arr.insert({ U"�", U"E" });
	symbol_arr.insert({ U"�", U"Yu" });
	symbol_arr.insert({ U"�", U"Ya" });
}

void Translator::translate_from_rus_into_en(std::u32string& string)
{
	if (symbol_arr.empty()) fill_symbol_arr();
	std::u32string old_string{ string };
	string.clear();
	for (auto& elem : old_string)
	{
		std::u32string string2;
		string2.clear();
		string2 += elem;
		auto iterator = symbol_arr.get<1>().find(string2);
		if (iterator!=symbol_arr.get<1>().end())
			string += iterator->latin;
	}
}

void Translator::translate_from_en_into_rus(std::u32string& string)
{
	if (symbol_arr.empty()) fill_symbol_arr();
	std::u32string old_string{ string };
	string.clear();
	for (auto& elem : old_string)
	{
		std::u32string string2;
		string2.clear();
		string2 += elem;
		auto iterator = symbol_arr.get<1>().find(string2);
		if (iterator != symbol_arr.get<1>().end())
			string += iterator->�yrillic;
	}
}