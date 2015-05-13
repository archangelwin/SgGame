#include "DbcTableManager.h"

const string DbcTableManager::RefrenceTableName = "refrence";

DbcTableManager::DbcTableManager()
:_mapDbcTable()
{
}

DbcTableManager::~DbcTableManager()
{
	map<string, DbcTable*>::iterator itTable = _mapDbcTable.begin();
	while (itTable != _mapDbcTable.end())
	{
		delete itTable->second;
		itTable->second = NULL;
		_mapDbcTable.erase(itTable);
	}
}


void DbcTableManager::addTable(DbcTable* table)
{
	ReturnVoidIfNull(table)

	map<string, DbcTable*>::iterator itTable = _mapDbcTable.find(table->getTableName());
	if (itTable != _mapDbcTable.end())
	{
		SG_TRACE2("table has already exist int the list:", table->getTableName());
		return;
	}

	_mapDbcTable.insert(map<string, DbcTable*>::value_type(table->getTableName(), table));
}

DbcTable* DbcTableManager::getTable(string name)
{
	map<string, DbcTable*>::iterator itTable = _mapDbcTable.find(name);
	if (itTable == _mapDbcTable.end())
	{
		return NULL;
	}

	return itTable->second;
}

bool DbcTableManager::checkRefrence()
{
	bool ret = true;

	DbcTable* pTable = getTable(RefrenceTableName);

	if (pTable == NULL)
	{
		ret = false;
		SG_TRACE("can't get refrence info");
		return ret;
	}

	if (pTable->getCol() < (int)DbcTable::MaxRefrence)
	{
		ret = false;
		SG_TRACE("refrence error!");
		return ret;
	}

	string tableNameSrc;
	string tableFieldSrc;
	string tableNameDst;
	string tableFieldDst;

	const vector<string>* listTableNameSrc = (pTable->getDataCol((int)DbcTable::TableNameSrc));
	const vector<string>* listTableFieldSrc = (pTable->getDataCol((int)DbcTable::TableFieldSrc));
	const vector<string>* listTableNameDst = (pTable->getDataCol((int)DbcTable::TableNameDst));
	const vector<string>* listTableFieldDst = (pTable->getDataCol((int)DbcTable::TableFieldDst));

	DbcTable* tableSrc = NULL;
	DbcTable* tableDst = NULL;
	const vector<string>* tableFieldSrcData;
	const vector<string>* tableFieldDstData;

	int i,len;
	for (i = (int)DbcTable::MaxRowDefine, len = pTable->getRow(); i < len; i++)
	{
		tableNameSrc = (*listTableNameSrc)[i];
		tableFieldSrc = (*listTableFieldSrc)[i];
		tableNameDst = (*listTableNameDst)[i];
		tableFieldDst = (*listTableFieldDst)[i];

		tableSrc = getTable(tableNameSrc);
		if (tableSrc == NULL)
		{
			ret = false;
			SG_TRACE2("can't find refrence src table:", tableNameSrc);
			continue;
		}

		tableFieldSrcData = (tableSrc->getDataCol(tableFieldSrc));
		if (tableFieldSrcData == NULL)
		{
			SG_TRACE3("can't find refrence src table field:", tableNameSrc, tableFieldSrc);
			continue;
		}

		tableDst = getTable(tableNameDst);
		if (tableDst == NULL)
		{
			ret = false;
			SG_TRACE2("can't find refrence dst table:", tableNameDst);
			continue;
		}
		tableFieldDstData = (tableDst->getDataCol(tableFieldDst));
		if (tableFieldSrcData == NULL)
		{
			ret = false;
			SG_TRACE3("can't find refrence dst table field:", tableNameDst, tableFieldDst);
			continue;
		}

		if (!DbcTable::checkRefrence(tableNameSrc, tableFieldSrcData, tableNameDst, tableFieldDstData))
		{
			ret = false;
		}
	}

	return ret;
}