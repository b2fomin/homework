#include"Translation.hpp"

Translator::symbol_multi_index Translator::symbol_arr{};

Translator::Translator()=default;

void Translator::fill_symbol_arr()
{
	symbol_arr.insert({ "�", "a"});
	symbol_arr.insert({ "�", "b" });
	symbol_arr.insert({ "�", "v" });
	symbol_arr.insert({ "�", "g" });
	symbol_arr.insert({ "�", "d" });
	symbol_arr.insert({ "�", "e" });
	symbol_arr.insert({ "�", "zh" });
	symbol_arr.insert({ "�", "z" });
	symbol_arr.insert({ "�", "i" });
	symbol_arr.insert({ "�", "y" });
	symbol_arr.insert({ "�", "k" });
	symbol_arr.insert({ "�", "l" });
	symbol_arr.insert({ "�", "m" });
	symbol_arr.insert({ "�", "n" });
	symbol_arr.insert({ "�", "o" });
	symbol_arr.insert({ "�", "p" });
	symbol_arr.insert({ "�", "r" });
	symbol_arr.insert({ "�", "s" });
	symbol_arr.insert({ "�", "t" });
	symbol_arr.insert({ "�", "u" });
	symbol_arr.insert({ "�", "f" });
	symbol_arr.insert({ "�", "kh" });
	symbol_arr.insert({ "�", "ts" });
	symbol_arr.insert({ "�", "ch" });
	symbol_arr.insert({ "�", "sh" });
	symbol_arr.insert({ "�", "shch" });
	symbol_arr.insert({ "�", "\"" });
	symbol_arr.insert({ "�", "y" });
	symbol_arr.insert({ "�", "\'" });
	symbol_arr.insert({ "�", "e" });
	symbol_arr.insert({ "�", "yu" });
	symbol_arr.insert({ "�", "ya" });
	symbol_arr.insert({ "�", "A" });
	symbol_arr.insert({ "�", "B" });
	symbol_arr.insert({ "�", "V" });
	symbol_arr.insert({ "�", "G" });
	symbol_arr.insert({ "�", "D" });
	symbol_arr.insert({ "�", "E" });
	symbol_arr.insert({ "�", "Zh" });
	symbol_arr.insert({ "�", "Z" });
	symbol_arr.insert({ "�", "I" });
	symbol_arr.insert({ "�", "Y" });
	symbol_arr.insert({ "�", "K" });
	symbol_arr.insert({ "�", "L" });
	symbol_arr.insert({ "�", "M" });
	symbol_arr.insert({ "�", "N" });
	symbol_arr.insert({ "�", "O" });
	symbol_arr.insert({ "�", "P" });
	symbol_arr.insert({ "�", "R" });
	symbol_arr.insert({ "�", "S" });
	symbol_arr.insert({ "�", "T" });
	symbol_arr.insert({ "�", "U" });
	symbol_arr.insert({ "�", "F" });
	symbol_arr.insert({ "�", "Kh" });
	symbol_arr.insert({ "�", "Ts" });
	symbol_arr.insert({ "�", "Ch" });
	symbol_arr.insert({ "�", "Sh" });
	symbol_arr.insert({ "�", "Shch" });
	symbol_arr.insert({ "�", "Y" });
	symbol_arr.insert({ "�", "E" });
	symbol_arr.insert({ "�", "Yu" });
	symbol_arr.insert({ "�", "Ya" });
}

void Translator::translate_from_rus_into_en(std::string& string)
{
	if (symbol_arr.empty()) fill_symbol_arr();
	std::string old_string{ string };
	string.clear();
	for (auto& elem : old_string)
	{
		auto iterator = symbol_arr.find(std::to_string(elem));
		if (iterator!=symbol_arr.end())
			string += iterator->latin;
	}
}

void Translator::translate_from_en_into_rus(std::string& string)
{
	if (symbol_arr.empty()) fill_symbol_arr();
	std::string old_string{ string };
	string.clear();
	for (auto& elem : old_string)
	{
		auto iterator = symbol_arr.get<1>().find(std::to_string(elem));
		if (iterator != symbol_arr.get<1>().end())
			string += iterator->�yrillic;
	}
}