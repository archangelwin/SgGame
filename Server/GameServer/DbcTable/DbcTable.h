/*!
 * \file DbcTable.h
 *
 * \author wuly
 * \date ËÄÔÂ 2015
 *
 * 
 */

#ifndef __DBCTABLE_H__
#define __DBCTABLE_H__

#include <SgLib.h>
#include <fstream>
#include <StringUtils.h>

using namespace std;

class DbcTable
{
public:
	DbcTable(string tableName);
	bool fillDataWithFile(ifstream file);
	int getCol();
	int getRow();

	inline string getTableName()
	{
		return _tableName;
	}

private:
	string _tableName;
	vector<vector<string>> _tableData;
};

#endif // __DbcTable_H__
