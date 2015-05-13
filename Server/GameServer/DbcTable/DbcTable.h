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
	enum RowDefine
	{
		FiledDesc = 0,
		FiledName,
		FiledType,
		MaxRowDefine,
	};

	enum RefrenceCol
	{
		TableNameSrc =0,
		TableFieldSrc,
		TableNameDst,
		TableFieldDst,
		MaxRefrence,
	};

	DbcTable(string tableName);
	bool fillDataWithFile(ifstream file);
	int getCol();
	int getRow();
	const vector<string>* getDataCol(string filedName);
	const vector<string>* getDataCol(int colIndex);

	inline string getTableName()
	{
		return _tableName;
	}

	static bool checkRefrence(const string tableNameSrc, const vector<string>* src, const string tableNameDst, const vector<string>* dst);
private:
	string _tableName;
	vector<vector<string>> _tableData;
};

#endif // __DbcTable_H__
