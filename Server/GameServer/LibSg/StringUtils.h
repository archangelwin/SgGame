/*!
 * \file StringUtils.h
 *
 * \author wuly
 * \date ÎåÔÂ 2015
 *
 * 
 */


#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include "SgLib.h"

using namespace std;

class StringUtils
{
public:
	static void trim(string& str, char chr);
	static vector<string> split(string& str, string pattern);
};

#endif // __StringUtils_H__
