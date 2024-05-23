#include "advanced_sync_info.h"
#include <iostream>

AdvancedSyncInfo::~AdvancedSyncInfo()
{
    for(auto tx : this->txpdos)
    {
        delete tx.pdo_list;
    }

    for(auto rx : this->rxpdos)
    {
        delete rx.pdo_list;
    }

    for(auto rx : this->rxpdo_entries)
    {
        delete[] rx;
    }

    for(auto tx : this->txpdo_entries)
    {
        delete[] tx;
    }
}

void AdvancedSyncInfo::AddTxPDO(uint16_t tx_mapping_index, PDOEntriesList* tx)
{
    txpdos.push_back({tx_mapping_index, tx});
}	

void AdvancedSyncInfo::AddRxPDO(uint16_t rx_mapping_index, PDOEntriesList* rx)
{
    rxpdos.push_back({rx_mapping_index, rx});
}

PDOEntriesList* AdvancedSyncInfo::GetRxPDO()
{
    return this->rxpdo_merged;
}

PDOEntriesList* AdvancedSyncInfo::GetTxPDO()
{
    return this->txpdo_merged;
}

ec_sync_info_t* AdvancedSyncInfo::GetSyncs()
{
    return this->syncs;
}

void AdvancedSyncInfo::DisableSM0()
{
    this->SM0_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM1()
{
    this->SM1_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM2()
{
    this->SM2_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM3()
{
    this->SM3_is_enabled = false;
}

void AdvancedSyncInfo::Create()
{
    this->PreparePDOs();

    uint16_t sync_size = 1 + SM0_is_enabled + SM1_is_enabled + SM2_is_enabled + SM3_is_enabled;
	syncs = new ec_sync_info_t[sync_size];

    int index = 0;
	if(SM0_is_enabled) 
    {
        syncs[index] = {0, EC_DIR_OUTPUT, 	0, NULL, EC_WD_DISABLE};
        ++index;
    }

    if(SM1_is_enabled)
    {
        syncs[index] = {1, EC_DIR_INPUT, 	0, NULL, EC_WD_DISABLE};
        ++index;
    }

    if(SM2_is_enabled)
    {
	    syncs[index] = {2, EC_DIR_OUTPUT, (uint16_t)rxpdos.size(), ec_rxpdo, EC_WD_ENABLE};
        ++index;
    }

    if(SM3_is_enabled)
    {
        syncs[index] = {3, EC_DIR_INPUT, (uint16_t)txpdos.size(), ec_txpdo, EC_WD_DISABLE};
        ++index;
    }
	syncs[index] = {0xff}; 

    this->SyncInfo::size = sync_size;
}

void AdvancedSyncInfo::PreparePDOs()
{
    if(!txpdos.empty())
    {
        ec_txpdo = new ec_pdo_info_t[txpdos.size()];
        txpdo_merged = new PDOEntriesList();
    }

    if(!rxpdos.empty())
    {
        ec_rxpdo = new ec_pdo_info_t[rxpdos.size()];
        rxpdo_merged = new PDOEntriesList();
    }

    for(int i = 0; i < txpdos.size(); ++i)
    {
        auto txpdo_map = txpdos.at(i).pdo_list->GetMap();
        ec_pdo_entry_info_t* current_pdo_entries = new ec_pdo_entry_info_t[txpdos.at(i).pdo_list->GetSize()];
        txpdo_entries.push_back(current_pdo_entries);

        int index = 0;
        for (auto it = txpdo_map->begin(); it != txpdo_map->end(); ++it)
        {
            current_pdo_entries[index] = {
                it->second->GetIndex(),
                it->second->GetSubindex(),
                it->second->GetSizeBit()
            };
            ++index;
        }
        ec_txpdo[i] = {txpdos.at(i).pdo_mapping_index, txpdos.at(i).pdo_list->GetSize(), current_pdo_entries};
        txpdo_merged->MergeWith(txpdos.at(i).pdo_list);
    }

    for(int i = 0; i < rxpdos.size(); ++i)
    {
        auto rxpdo_map = rxpdos.at(i).pdo_list->GetMap();
        ec_pdo_entry_info_t* current_pdo_entries = new ec_pdo_entry_info_t[rxpdos.at(i).pdo_list->GetSize()];
        rxpdo_entries.push_back(current_pdo_entries);

        int index = 0;
        for (auto it = rxpdo_map->begin(); it != rxpdo_map->end(); ++it)
        {
            current_pdo_entries[index] = {
                it->second->GetIndex(),
                it->second->GetSubindex(),
                it->second->GetSizeBit()
            };
            ++index;
        }
        ec_rxpdo[i] = {rxpdos.at(i).pdo_mapping_index, rxpdos.at(i).pdo_list->GetSize(), current_pdo_entries};
        rxpdo_merged->MergeWith(rxpdos.at(i).pdo_list);
    }
    // DEBUG OUTPUT
    /*for(int i = 0; i < txpdos.size(); ++i)
    {
        std::cout << "ec_txpdo: " << ec_txpdo->index << " " << ec_txpdo->n_entries << "\n";
    }

    for(int i = 0; i < rxpdos.size(); ++i)
    {
        std::cout << "ec_rxpdo: " << ec_rxpdo->index << " " << ec_rxpdo->n_entries << "\n";
    } */


    // DEBUG OUTPUT
    /*std::cout << "RxPDOs:\n" << std::endl;
    auto rx_map = rxpdo_merged->GetMap();
    //std::cout << "SIZE: " << rx_map->size() << "\n";
    for(auto it = rx_map->begin(); it != rx_map->end(); ++it)
    {
        std::cout << "\t" << std::hex << it->second->GetIndex() + 0 << ":" << it->second->GetSubindex() + 0 << " " << it->second->GetSizeBit() + 0 << "\n";
    }

    std::cout << "TxPDOs:\n" << std::endl;
    auto tx_map = txpdo_merged->GetMap();
    for(auto it = tx_map->begin(); it != tx_map->end(); ++it)
    {
        std::cout << "\t" << std::hex << it->second->GetIndex() + 0 << ":" << it->second->GetSubindex() + 0 << " " << it->second->GetSizeBit() + 0 << "\n";
    }  */
}