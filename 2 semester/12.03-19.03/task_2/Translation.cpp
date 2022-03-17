#include"Translation.hpp"

Translator::symbol_multi_index Translator::symbol_arr{};

Translator::Translator()=default;

void Translator::fill_symbol_arr()
{
	symbol_arr.insert({ "à", "a"});
	symbol_arr.insert({ "á", "b" });
	symbol_arr.insert({ "â", "v" });
	symbol_arr.insert({ "ã", "g" });
	symbol_arr.insert({ "ä", "d" });
	symbol_arr.insert({ "å", "e" });
	symbol_arr.insert({ "æ", "zh" });
	symbol_arr.insert({ "ç", "z" });
	symbol_arr.insert({ "è", "i" });
	symbol_arr.insert({ "é", "y" });
	symbol_arr.insert({ "ê", "k" });
	symbol_arr.insert({ "ë", "l" });
	symbol_arr.insert({ "ì", "m" });
	symbol_arr.insert({ "í", "n" });
	symbol_arr.insert({ "î", "o" });
	symbol_arr.insert({ "ï", "p" });
	symbol_arr.insert({ "ð", "r" });
	symbol_arr.insert({ "ñ", "s" });
	symbol_arr.insert({ "ò", "t" });
	symbol_arr.insert({ "ó", "u" });
	symbol_arr.insert({ "ô", "f" });
	symbol_arr.insert({ "õ", "kh" });
	symbol_arr.insert({ "ö", "ts" });
	symbol_arr.insert({ "÷", "ch" });
	symbol_arr.insert({ "ø", "sh" });
	symbol_arr.insert({ "ù", "shch" });
	symbol_arr.insert({ "ú", "\"" });
	symbol_arr.insert({ "û", "y" });
	symbol_arr.insert({ "ü", "\'" });
	symbol_arr.insert({ "ý", "e" });
	symbol_arr.insert({ "þ", "yu" });
	symbol_arr.insert({ "ÿ", "ya" });
	symbol_arr.insert({ "À", "A" });
	symbol_arr.insert({ "Á", "B" });
	symbol_arr.insert({ "Â", "V" });
	symbol_arr.insert({ "Ã", "G" });
	symbol_arr.insert({ "Ä", "D" });
	symbol_arr.insert({ "Å", "E" });
	symbol_arr.insert({ "Æ", "Zh" });
	symbol_arr.insert({ "Ç", "Z" });
	symbol_arr.insert({ "È", "I" });
	symbol_arr.insert({ "É", "Y" });
	symbol_arr.insert({ "Ê", "K" });
	symbol_arr.insert({ "Ë", "L" });
	symbol_arr.insert({ "Ì", "M" });
	symbol_arr.insert({ "Í", "N" });
	symbol_arr.insert({ "Î", "O" });
	symbol_arr.insert({ "Ï", "P" });
	symbol_arr.insert({ "Ð", "R" });
	symbol_arr.insert({ "Ñ", "S" });
	symbol_arr.insert({ "Ò", "T" });
	symbol_arr.insert({ "Ó", "U" });
	symbol_arr.insert({ "Ô", "F" });
	symbol_arr.insert({ "Õ", "Kh" });
	symbol_arr.insert({ "Ö", "Ts" });
	symbol_arr.insert({ "×", "Ch" });
	symbol_arr.insert({ "Ø", "Sh" });
	symbol_arr.insert({ "Ù", "Shch" });
	symbol_arr.insert({ "Û", "Y" });
	symbol_arr.insert({ "Ý", "E" });
	symbol_arr.insert({ "Þ", "Yu" });
	symbol_arr.insert({ "ß", "Ya" });
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
			string += iterator->ñyrillic;
	}
}