#include "Figure.hpp"

std::ostream& operator<<(std::ostream& out, const Figure& figure)
{
	for (int i = 0; i < figure.size; ++i)
	{
		static int current = 0;
		for (int j = 0; j < figure.size; ++j)
		{
			if (j != figure.figure[current].first) out << " ";
			else
			{
				out << "*";
				++current;
			}
		}
		out << std::endl;
	}
}