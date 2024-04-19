#include "default_sync_info.h"

DefaultSyncInfo::~DefaultSyncInfo()
{
	delete rxpdo;
	delete txpdo;
	delete[] rxpdo_entries;		
	delete[] txpdo_entries;
	delete[] pdos;
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
	if(this->rxpdo && this->txpdo)
	{
		auto rxpdo_map = rxpdo->GetMap();		
		auto txpdo_map = txpdo->GetMap();
		rxpdo_entries = new ec_pdo_entry_info_t[rxpdo->GetSize()];
		txpdo_entries = new ec_pdo_entry_info_t[txpdo->GetSize()];

		int index = 0;
		for(auto it = rxpdo_map->begin(); it != rxpdo_map->end(); ++it)
		{
			rxpdo_entries[index++] = {
				it->second->GetIndex(),
				it->second->GetSubindex(),
				it->second->GetSizeBit()				
			};
		}			

		index = 0;
		for(auto it = txpdo_map->begin(); it != txpdo_map->end(); ++it)
		{
			txpdo_entries[index++] = {
				it->second->GetIndex(),
				it->second->GetSubindex(),
				it->second->GetSizeBit()				
			};
		}	

		pdos = new ec_pdo_info_t[2];
		pdos[0] = {rxpdo_mapping, rxpdo->GetSize(), rxpdo_entries};
		pdos[1] = {txpdo_mapping, txpdo->GetSize(), txpdo_entries};

		syncs = new ec_sync_info_t[5];
		syncs[0] = {0, EC_DIR_OUTPUT, 	0, NULL, EC_WD_DISABLE};
		syncs[1] = {1, EC_DIR_INPUT, 	0, NULL, EC_WD_DISABLE};
		syncs[2] = {2, EC_DIR_OUTPUT, 	1, pdos + 0, EC_WD_ENABLE};
		syncs[3] = {3, EC_DIR_INPUT, 	1, pdos + 1, EC_WD_DISABLE};
		syncs[4] = {0xff};
	}
}