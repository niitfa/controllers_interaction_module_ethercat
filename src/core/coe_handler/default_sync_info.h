/**
 * @brief Derived from SyncInfo (see description). Used for creating 
 * 1 TxPDO and 1 RxPDO mapping (with any objects setup).
 * @details Configuration example:
 * @code
 * #include "default_sync_info.h"
 * #include "pdo_entries_list.h"
 * 
 * void ConfigureSyncInfo()
 * {
 * 		PDOEntriesList *rxpdo, *txpdo;
 * 
 * 		// Let's say rxpdo and txpdo were previously configured.
 * 		// See PDOEntriesList configuration example in class description.
 * 
 * 		DefaultSyncInfo* sync = new DefaultSyncInfo();
 * 		sync->AddRxPDO(0x1600, rxpdo);
 * 		sync->AddTxPDO(0x1A00, txpdo);
 * 		sync->Create();
 * }
 * @endcode
 * @see SyncInfo, PDOEntriesList
 */

#ifndef DEFAULT_SYNC_INFO_H
#define DEFAULT_SYNC_INFO_H

#include "sync_info.h"

class DefaultSyncInfo : public SyncInfo
{
protected:
	PDOEntriesList *txpdo = nullptr;
	PDOEntriesList *rxpdo = nullptr;
	uint16_t txpdo_mapping, rxpdo_mapping;
	ec_pdo_entry_info_t *txpdo_entries = nullptr;
	ec_pdo_entry_info_t *rxpdo_entries = nullptr;
	ec_sync_info_t* syncs = nullptr;

	ec_pdo_info_t* ec_txpdo = NULL;
	ec_pdo_info_t* ec_rxpdo = NULL;	

public:
	DefaultSyncInfo() = default;
	~DefaultSyncInfo();
	/**
	 * @brief Adds TxPDO.
	 * @param[in] txpdo Mapping index.
	 * @param[in] tx PDO content.
	*/
	void AddTxPDO(uint16_t tx_mapping, PDOEntriesList* tx);	
	/**
	 * @brief Adds RxPDO.
	 * @param[in] txpdo Mapping index.
	 * @param[in] tx PDO content.
	*/
	void AddRxPDO(uint16_t rx_mapping, PDOEntriesList* rx);
	/**
	 * @brief See SyncInfo::GetRxPDO().
	*/
	PDOEntriesList* GetRxPDO() override;
	/**
	 * @brief See SyncInfo::GetTxPDO().
	*/
	PDOEntriesList* GetTxPDO() override;
	/**
	 * @brief See SyncInfo::GetSyncs().
	*/
	ec_sync_info_t* GetSyncs() override;
	/**
	 * @brief See SyncInfo::Create().
	*/
	void Create() override;	
protected:
	void PreparePDOs();
};

#endif