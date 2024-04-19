#ifndef SYNC_INFO_H
#define SYNC_INFO_H

#include "ecrt.h"
#include "coe_process_object.h"
#include "pdo_entries_list.h"
#include <map>
#include <vector>

class SyncInfo
{
public:
	virtual ~SyncInfo() = default;
	virtual void Create() = 0;
	virtual PDOEntriesList* GetRxPDO() = 0;
	virtual PDOEntriesList* GetTxPDO() = 0;	
	virtual ec_sync_info_t* GetSyncs() = 0;
};

#endif