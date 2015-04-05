#include "StringUtils.h"

void StringUtils::trim(string& str, char chr)
{
	string::size_type pos = str.find_first_of(chr);
	while (pos != string::npos)
	{
		str.erase(pos, 1);
		pos = str.find_first_of(chr);
	}
}