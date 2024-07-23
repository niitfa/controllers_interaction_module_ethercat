#ifndef ODOT_CN_8033_SYNC_INFO_H
#define ODOT_CN_8033_SYNC_INFO_H

#include "sync_info.h"

class ODOT_CN_8033_SyncInfo : public SyncInfo
{
    PDOEntriesList *rxpdo = nullptr;
    ec_pdo_entry_info_t *rxpdo_entries = nullptr; 
	ec_pdo_info_t* ec_rxpdo = nullptr;

    PDOEntriesList *txpdo_ct_3168 = nullptr;
    ec_pdo_entry_info_t *txpdo_ct_3168_entries = nullptr;
	ec_pdo_info_t* ec_txpdo = nullptr;

	ec_sync_info_t* syncs = nullptr;
    ec_slave_config_t* slave_config = nullptr;
public:
    ~ODOT_CN_8033_SyncInfo();
    void Create() override;
    PDOEntriesList* GetRxPDO() override;
    PDOEntriesList* GetTxPDO() override;
    ec_sync_info_t* GetSyncs() override;
    void SetSlaveConfig(ec_slave_config_t* sc);
private:
    void CopyPDOtoIgHStruct(PDOEntriesList* pdo, ec_pdo_entry_info_t** igh_pdo_entries);
};

#endif