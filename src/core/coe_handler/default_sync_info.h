#ifndef DEFAULT_SYNC_INFO_H
#define DEFAULT_SYNC_INFO_H

#include "sync_info.h"

/*!
 * @brief Default sync info
*/
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
	/**
	 * @brief Add txpdo
	 * @param txpdo mapping index
	 * @param txpdo
	*/
	void AddTxPDO(uint16_t tx_mapping, PDOEntriesList* tx);	
	void AddRxPDO(uint16_t rx_mapping, PDOEntriesList* rx);
	PDOEntriesList* GetRxPDO() override;
	PDOEntriesList* GetTxPDO() override;
	ec_sync_info_t* GetSyncs() override;
	void Create() override;	
};

#endif