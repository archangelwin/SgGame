//  [5/13/2015 wuliangyu]

#ifndef __DBCTABLEMANAGER_H__
#define __DBCTABLEMANAGER_H__

#include <SgLib.h>
#include "DbcTable.h"

class DbcTableManager
{
public:
	DbcTableManager();
	~DbcTableManager();

	void addTable(DbcTable* table);
	DbcTable* getTable(string name);

	static const string RefrenceTableName;

private:
	std::map<string, DbcTable*> _mapDbcTable;
};

#endif // __DBCTABLEMANAGER_h__