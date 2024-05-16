#include "odot_cn_8033_sync_info.h"
#include <iostream>

ODOT_CN_8033_SyncInfo::~ODOT_CN_8033_SyncInfo()
{
    delete rxpdo;
 	delete[] rxpdo_entries;
 	delete[] ec_rxpdo; 

	delete txpdo_ct_3168;
	delete[] txpdo_ct_3168_entries;
	delete[] ec_txpdo;
	delete[] syncs;
}

void ODOT_CN_8033_SyncInfo::Create()
{
    /* merge pdos in future !!! */
    uint16_t txpdo_ct_3168_mapping_index = 0x1A00;
    txpdo_ct_3168 = new PDOEntriesList();
    txpdo_ct_3168->AddEntry("Ch#1", 0x6000, 0x01, 16);

    this->CopyPDOtoIgHStruct(txpdo_ct_3168, &txpdo_ct_3168_entries);

    ec_pdo_info_t* ec_ct_3168_txpdo = new ec_pdo_info_t; // TxPDO №1
    *ec_ct_3168_txpdo = {txpdo_ct_3168_mapping_index, txpdo_ct_3168->GetSize(), txpdo_ct_3168_entries}; // TxPDO №1

    std::cout << "ec_ct_3168_txpdo: " << ec_ct_3168_txpdo->entries << std::endl;

    /* Full TxPDO */
    uint16_t number_of_txpdos = 1;
    ec_txpdo = new ec_pdo_info_t[number_of_txpdos];
    ec_txpdo[0] = *ec_ct_3168_txpdo; // TxPDO №1
    delete ec_ct_3168_txpdo;

	uint16_t sync_size = 4;
	syncs = new ec_sync_info_t[sync_size];
	syncs[0] = {0, EC_DIR_OUTPUT, 	0, NULL, EC_WD_DISABLE};
	syncs[1] = {1, EC_DIR_INPUT, 	0, NULL, EC_WD_DISABLE};
	syncs[2] = {3, EC_DIR_INPUT, 	number_of_txpdos, ec_txpdo, EC_WD_DISABLE};
	syncs[3] = {0xff}; 

	this->SyncInfo::size = sync_size;
}

PDOEntriesList* ODOT_CN_8033_SyncInfo::GetRxPDO()
{
    return this->rxpdo;
}

PDOEntriesList* ODOT_CN_8033_SyncInfo::GetTxPDO()
{
    return this->txpdo_ct_3168;
}

ec_sync_info_t* ODOT_CN_8033_SyncInfo::GetSyncs()
{
    return this->syncs;
}

void ODOT_CN_8033_SyncInfo::SetSlaveConfig(ec_slave_config_t* sc)
{
    this->slave_config = sc;
}

void ODOT_CN_8033_SyncInfo::CopyPDOtoIgHStruct(PDOEntriesList* pdo, ec_pdo_entry_info_t** igh_pdo_entries)
{
     if(pdo) // in other function?
    {
        int index = 0;
        auto txpdo_map = pdo->GetMap();
        *igh_pdo_entries = new ec_pdo_entry_info_t[pdo->GetSize()];
        for(auto it = txpdo_map->begin(); it != txpdo_map->end(); ++it)
		{
			*igh_pdo_entries[index++] = {
				it->second->GetIndex(),
				it->second->GetSubindex(),
				it->second->GetSizeBit()				
			};
		}
    }   
}