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
	return _tableData.size();
}

int DbcTable::getRow()
{
	return _tableData[0].size();
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

const vector<string>* DbcTable::getDataCol(int index)
{
	if (index < _tableData.size())
	{
		_tableData[index];
	}

	return NULL;
}

bool DbcTable::checkRefrence(const string tableNameSrc, const vector<string>* src, const string tableNameDst, const vector<string>* dst)
{
	ReturnFalseIfNull(src)
	ReturnFalseIfNull(dst)

	if (src->size() < (int)MaxRowDefine)
	{
		return false;
	}
	
	if (dst->size() < (int)MaxRowDefine)
	{
		return false;
	}

	bool ret = true;
	vector<string>::size_type i, j, len, len2;
	char strLog[200];
	for (i = (vector<string>::size_type)MaxRowDefine, len=src->size(); i < len; i++)
	{
		for (j = (vector<string>::size_type)MaxRowDefine, len2 = dst->size(); j < len2; j++)
		{
			if ((*src)[i] == (*dst)[j])
			{
				break;
			}
		}

		ret = false;
		memset(strLog, 0x00, sizeof(strLog));
		sprintf_s(strLog, sizeof(strLog), "failed find refrence, srcTableName=%s srcFiledName=%s dstTableName=%s dstFiledName=%s value=%s row=%d", tableNameSrc, (*src)[FiledName], tableNameDst, (*dst)[FiledName], (*src)[i], i);
		SG_TRACE(strLog);
	}

	return ret;
}