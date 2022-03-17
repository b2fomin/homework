#include"Translation.hpp"

Translator::symbol_multi_index Translator::symbol_arr{};

Translator::Translator()=default;

void Translator::fill_symbol_arr()
{
	symbol_arr.insert({ U"à", U"a"});
	symbol_arr.insert({ U"á", U"b" });
	symbol_arr.insert({ U"â", U"v" });
	symbol_arr.insert({ U"ã", U"g" });
	symbol_arr.insert({ U"ä", U"d" });
	symbol_arr.insert({ U"å", U"e" });
	symbol_arr.insert({ U"æ", U"zh" });
	symbol_arr.insert({ U"ç", U"z" });
	symbol_arr.insert({ U"è", U"i" });
	symbol_arr.insert({ U"é", U"y" });
	symbol_arr.insert({ U"ê", U"k" });
	symbol_arr.insert({ U"ë", U"l" });
	symbol_arr.insert({ U"ì", U"m" });
	symbol_arr.insert({ U"í", U"n" });
	symbol_arr.insert({ U"î", U"o" });
	symbol_arr.insert({ U"ï", U"p" });
	symbol_arr.insert({ U"ğ", U"r" });
	symbol_arr.insert({ U"ñ", U"s" });
	symbol_arr.insert({ U"ò", U"t" });
	symbol_arr.insert({ U"ó", U"u" });
	symbol_arr.insert({ U"ô", U"f" });
	symbol_arr.insert({ U"õ", U"kh" });
	symbol_arr.insert({ U"ö", U"ts" });
	symbol_arr.insert({ U"÷", U"ch" });
	symbol_arr.insert({ U"ø", U"sh" });
	symbol_arr.insert({ U"ù", U"shch" });
	symbol_arr.insert({ U"ú", U"\"" });
	symbol_arr.insert({ U"û", U"y" });
	symbol_arr.insert({ U"ü", U"\'" });
	symbol_arr.insert({ U"ı", U"e" });
	symbol_arr.insert({ U"ş", U"yu" });
	symbol_arr.insert({ U"ÿ", U"ya" });
	symbol_arr.insert({ U"À", U"A" });
	symbol_arr.insert({ U"Á", U"B" });
	symbol_arr.insert({ U"Â", U"V" });
	symbol_arr.insert({ U"Ã", U"G" });
	symbol_arr.insert({ U"Ä", U"D" });
	symbol_arr.insert({ U"Å", U"E" });
	symbol_arr.insert({ U"Æ", U"Zh" });
	symbol_arr.insert({ U"Ç", U"Z" });
	symbol_arr.insert({ U"È", U"I" });
	symbol_arr.insert({ U"É", U"Y" });
	symbol_arr.insert({ U"Ê", U"K" });
	symbol_arr.insert({ U"Ë", U"L" });
	symbol_arr.insert({ U"Ì", U"M" });
	symbol_arr.insert({ U"Í", U"N" });
	symbol_arr.insert({ U"Î", U"O" });
	symbol_arr.insert({ U"Ï", U"P" });
	symbol_arr.insert({ U"Ğ", U"R" });
	symbol_arr.insert({ U"Ñ", U"S" });
	symbol_arr.insert({ U"Ò", U"T" });
	symbol_arr.insert({ U"Ó", U"U" });
	symbol_arr.insert({ U"Ô", U"F" });
	symbol_arr.insert({ U"Õ", U"Kh" });
	symbol_arr.insert({ U"Ö", U"Ys" });
	symbol_arr.insert({ U"×", U"Ch" });
	symbol_arr.insert({ U"Ø", U"Sh" });
	symbol_arr.insert({ U"Ù", U"Shch" });
	symbol_arr.insert({ U"Ú", U"\"" });
	symbol_arr.insert({ U"Û", U"Y" });
	symbol_arr.insert({ U"Ü", U"\'" });
	symbol_arr.insert({ U"İ", U"E" });
	symbol_arr.insert({ U"Ş", U"Yu" });
	symbol_arr.insert({ U"ß", U"Ya" });
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
			string += iterator->ñyrillic;
	}
}