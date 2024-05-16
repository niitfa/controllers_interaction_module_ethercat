#include "default_sync_info.h"
#include <iostream>

DefaultSyncInfo::~DefaultSyncInfo()
{
	delete rxpdo;
	delete txpdo;
	delete[] rxpdo_entries;		
	delete[] txpdo_entries;
	delete ec_txpdo;
	delete ec_rxpdo;
	delete[] syncs;
}

void DefaultSyncInfo::AddTxPDO(uint16_t tx_mapping, PDOEntriesList* tx)
{
	this->txpdo = tx;
	this->txpdo_mapping = tx_mapping;
}	
void DefaultSyncInfo::AddRxPDO(uint16_t rx_mapping, PDOEntriesList* rx)
{
	this->rxpdo = rx;
	this->rxpdo_mapping = rx_mapping;
}
PDOEntriesList* DefaultSyncInfo::GetRxPDO() { return this->rxpdo; }
PDOEntriesList* DefaultSyncInfo::GetTxPDO() { return this->txpdo; }
ec_sync_info_t* DefaultSyncInfo::GetSyncs() { return this->syncs; }

void DefaultSyncInfo::Create()
{
	this->PreparePDOs();

	uint16_t sync_size = 5;
	syncs = new ec_sync_info_t[sync_size];
	syncs[0] = {0, EC_DIR_OUTPUT, 	0, NULL, EC_WD_DISABLE};
	syncs[1] = {1, EC_DIR_INPUT, 	0, NULL, EC_WD_DISABLE};
	syncs[2] = {2, EC_DIR_OUTPUT, 	1, ec_rxpdo, EC_WD_ENABLE};
	syncs[3] = {3, EC_DIR_INPUT, 	1, ec_txpdo, EC_WD_DISABLE};
	syncs[4] = {0xff}; 

	this->SyncInfo::size = sync_size;
}

void DefaultSyncInfo::PreparePDOs()
{
	if(rxpdo)
	{
		int index = 0;
		auto rxpdo_map = rxpdo->GetMap();
		rxpdo_entries = new ec_pdo_entry_info_t[rxpdo->GetSize()];

		for(auto it = rxpdo_map->begin(); it != rxpdo_map->end(); ++it)
		{
			rxpdo_entries[index++] = {
				it->second->GetIndex(),
				it->second->GetSubindex(),
				it->second->GetSizeBit()				
			};
		}
			
		ec_rxpdo = new ec_pdo_info_t;
		*ec_rxpdo = {rxpdo_mapping, rxpdo->GetSize(), rxpdo_entries};
	}		

	if(txpdo)
	{
		int index = 0;
		auto txpdo_map = txpdo->GetMap();
		txpdo_entries = new ec_pdo_entry_info_t[txpdo->GetSize()];		
		for(auto it = txpdo_map->begin(); it != txpdo_map->end(); ++it)
		{
			txpdo_entries[index++] = {
				it->second->GetIndex(),
				it->second->GetSubindex(),
				it->second->GetSizeBit()				
			};
		}

		ec_txpdo = new ec_pdo_info_t;	
		*ec_txpdo = {txpdo_mapping, txpdo->GetSize(), txpdo_entries};
	}		
}