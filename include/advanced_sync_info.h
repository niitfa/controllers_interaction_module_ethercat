#ifndef ADVANCED_SYNC_INFO_H
#define ADVANCED_SYNC_INFO_H

#include "default_sync_info.h"
#include <vector>

class AdvancedSyncInfo : public SyncInfo
{
    struct IndexedPDO
    {
        uint16_t pdo_mapping_index;     
        PDOEntriesList* pdo_list;
    };

    std::vector<IndexedPDO> txpdos, rxpdos;
    std::vector<ec_pdo_entry_info_t*> txpdo_entries, rxpdo_entries;

    PDOEntriesList* txpdo_merged = nullptr;
    PDOEntriesList* rxpdo_merged = nullptr;

    ec_sync_info_t* syncs = nullptr;
	ec_pdo_info_t* ec_txpdo = nullptr;
	ec_pdo_info_t* ec_rxpdo = nullptr;	

    bool SM0_is_enabled = true;
    bool SM1_is_enabled = true;
    bool SM2_is_enabled = true;
    bool SM3_is_enabled = true;
public:
    AdvancedSyncInfo() = default;
    ~AdvancedSyncInfo();

    /**
	 * @brief Adds TxPDO.
	 * @param[in] txpdo Mapping index.
	 * @param[in] tx PDO content.
	*/
	void AddTxPDO(uint16_t tx_mapping_index, PDOEntriesList* tx);	
	/**
	 * @brief Adds RxPDO.
	 * @param[in] txpdo Mapping index.
	 * @param[in] tx PDO content.
	*/
	void AddRxPDO(uint16_t rx_mapping_index, PDOEntriesList* rx);
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

    void DisableSM0();
    void DisableSM1();
    void DisableSM2();
    void DisableSM3();

    void Create() override;
private:
    void PreparePDOs();

};

#endif