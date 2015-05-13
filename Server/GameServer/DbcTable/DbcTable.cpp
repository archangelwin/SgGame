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

const vector<string>* DbcTable::getDataCol(string filedName)
{
	vector<vector<string>>::iterator it = _tableData.begin();
	for (it = _tableData.begin(); it != _tableData.end(); it++)
	{
		if ((*it)[(int)FiledName] == filedName)
		{
			return &(*it);
		}
	}
	
	return NULL;
}

bool DbcTable::checkRefrence(vector<string>* src, vector<string>* dst)
{
	ReturnFalseIfNull(src)
	ReturnFalseIfNull(dst)

	if (src->size() < (int)RowDefineMax)
	{
		return false;
	}
	
	if (dst->size() < (int)RowDefineMax)
	{
		return false;
	}

	bool ret = true;
	vector<string>::size_type i, j, len, len2;
	for (i = (vector<string>::size_type)RowDefineMax, len=src->size(); i < len; i++)
	{
		for (j = (vector<string>::size_type)RowDefineMax, len2 = dst->size(); j < len2; j++)
		{
			if ((*src)[i] == (*dst)[j])
			{
				break;
			}
		}

		ret = false;
		SG_TRACE3("filed refrence error, filed value:", (*src)[FiledName], (*src)[i]);
	}

	return ret;
}