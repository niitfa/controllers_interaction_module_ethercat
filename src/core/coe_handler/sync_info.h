/**
 * @brief Basic class. Stores slave's PDOs and mappings.
 * Member of EthercatSlave.
 * @see EthercatSlave.
*/

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
	/**
	 * @brief Ends configuration. Call this method
	 * before passing SyncInfo to EthercatSlave instance and
	 * do not call any other SyncInfo method after. 
	*/
	virtual void Create() = 0;
	/**
	 * @brief Gets RxPDOs.
	 * @returns Pointer to previously passed PDOEntriesList.
	 * @warning Must NOT be called by user!
	*/
	virtual PDOEntriesList* GetRxPDO() = 0;
	/**
	 * @brief Gets TxPDOs.
	 * @returns Pointer to previously passed PDOEntriesList.
	 * @warning Must NOT be called by user!
	*/
	virtual PDOEntriesList* GetTxPDO() = 0;
	/**
	 * @brief Gets IgH syncs.
	 * @returns Pointer to ec_sync_info_t.
	 * @warning Must NOT be called by user!
	*/
	virtual ec_sync_info_t* GetSyncs() = 0;
};

#endif