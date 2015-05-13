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