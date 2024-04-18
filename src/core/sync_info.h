#ifndef SYNCINFO_H
#define SYNCINFO_H

#include "ecrt.h"
#include "coe_process_object.h"
#include <map>
#include <vector>

class PDOEntriesList
{
	std::map<std::string, CoEProcessObject*> pdo_entries;
public:
	PDOEntriesList() = default;
	~PDOEntriesList();
	void AddEntry(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	std::map<std::string, CoEProcessObject*>* GetMap();
	uint16_t GetSize();
	CoEProcessObject* GetEntry(std::string name);
};

class SyncInfo
{
public:
	virtual ~SyncInfo() = default;
	virtual void Create() = 0;
	virtual PDOEntriesList* GetRxPDO() = 0;
	virtual PDOEntriesList* GetTxPDO() = 0;	
	virtual ec_sync_info_t* GetSyncs() = 0;
};

class DefaultSyncInfo : public SyncInfo
{
	PDOEntriesList *txpdo = nullptr;
	PDOEntriesList *rxpdo = nullptr;
	uint16_t txpdo_mapping, rxpdo_mapping;
	ec_pdo_entry_info_t *txpdo_entries = nullptr;
	ec_pdo_entry_info_t *rxpdo_entries = nullptr;
	ec_pdo_info_t* pdos = nullptr;
	ec_sync_info_t* syncs = nullptr;

public:
	DefaultSyncInfo() = default;
	~DefaultSyncInfo();
	void AddTxPDO(uint16_t tx_mapping, PDOEntriesList* tx);	
	void AddRxPDO(uint16_t rx_mapping, PDOEntriesList* rx);
	PDOEntriesList* GetRxPDO() override;
	PDOEntriesList* GetTxPDO() override;
	ec_sync_info_t* GetSyncs() override;
	void Create() override;	
};

#endif