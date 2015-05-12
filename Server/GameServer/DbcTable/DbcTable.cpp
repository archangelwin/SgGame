#include "DbcTable.h"

DbcTable::DbcTable(string tableName)
:_tableName(tableName),
_tableData()
{
}

bool DbcTable::fillDataWithFile(ifstream file)
{
	string strLine;
	vector<string> lineData;
	string pattern = "\t";
	_tableData.clear();
	while (getline(file, strLine))
	{
		_tableData.push_back(StringUtils::split(strLine, pattern));
	}

	SG_TRACE2("fillDataWithFile row count:", getRow());

	return true;
}

int DbcTable::getCol()
{
	if (_tableData.empty())
	{
		return 0;
	}
	return _tableData[0].size();
}

int DbcTable::getRow()
{
	return _tableData.size();
}