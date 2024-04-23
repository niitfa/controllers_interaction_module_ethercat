/**
 * @brief Contains ethercat master properties and methods.
 * Member of EthercatConfiguration.
 * @details
 * Configuration example:
 * @code
 * #include "ethercat_master.h"
 * 
 * void ConfigureMaster()
 * {
 * 		EthercatMaster* master = new EthercatMaster();	
 * 		master->SetMasterIndex(0);
 * }
 * @endcode
 * @see EthercatConfiguration.
*/

#ifndef ETHERCAT_MASTER_H
#define ETHERCAT_MASTER_H

#include "ecrt.h"
#include "mailbox_manager.h"

class EthercatMaster
{
	ec_master_t* master_request = nullptr;
	int master_index;
public:
	EthercatMaster();
	~EthercatMaster();
	/**
	 * @brief Sets network interface which will be used as ethercat master.
	 * @details List of created masters with their mac addresses is given in /etc/sysconfig/ethercat file
	 * 
	 * #<br> 
	 * MASTER<X>_DEVICE = "mac_address"<br>
	 * #<br>
	 * where <X> - master index.<br>
	 * 
	 * Example:
	 * If config file contains MASTER0_DEVICE = "00:1b:22:57:36:e6",
	 * pass 0 to this function for using following network interface as ethercat master.
	 * @param[in] int master index.
	*/
	void SetMasterIndex(int);
	/**
	 * @brief Ethercat master initial request.
	 * @warning Must NOT be called by user!
	*/	
	void Request();
	/**
	 * @brief Gets ethercat master request.
	 * @returns Ethercat master request.
	*/
	ec_master_t* GetRequest();
	/**
	 * @brief Wrapper for IgH function ecrt_master_activate(ec_master_t*).
	 * @warning Must NOT be called by user!
	*/
	void Activate();
	/**
	 * @brief Wrapper for IgH function ecrt_release_master(ec_master_t*).
	 * @warning Must NOT be called by user!
	*/
	void Release();
	/**
	 * @brief Wrapper for IgH function ecrt_master_receive(ec_master_t*).
	 * @warning Must NOT be called by user!
	*/
	void ReceiveProcessData();
	/**
	 * @brief Wrapper for IgH function ecrt_master_send(ec_master_t*).
	 * @warning Must NOT be called by user!
	*/
	void SendProcessData();
};

#endif