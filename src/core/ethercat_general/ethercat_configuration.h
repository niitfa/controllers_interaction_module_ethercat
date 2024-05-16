/**
 * @brief This class contains general ethercat network properties,
 * e.g. master, slaves, timer, domain. Designed for passing in main interface 
 * instance of EthercatThreadManager.
 * @warning For normal behaviour in EthercatThreadManager context 
 * (e.g. calling all ethercat exchange related functions) previously configured
 * EthercatMaster, EthercatSlavesContainer, EthercatTimer instances must be registered.
 * @see EthercatThreadManager, EthercatMaster, EthercatSlavesContainer, EthercatTimer
*/

#ifndef ETHERCAT_CONFIGURATION_H
#define ETHERCAT_CONFIGURATION_H

#include <vector>
#include <map>

#include "ecrt.h"
#include "ethercat_slaves_container.h"
#include "ethercat_master.h"
#include "ethercat_timer.h"
#include "ethercat_domain.h"
#include "ethercat_network_telemetry.h"
#include "ethercat_telemetry_broker.h"
#include "mailbox_manager.h"


class EthercatConfiguration
{
	EthercatMaster* master = nullptr;
	EthercatSlavesContainer* slaves = nullptr;	
	EthercatTimer* timer = nullptr;	
	EthercatDomain* domain = nullptr;
	EthercatTelemetryBroker* telemetry_broker = nullptr;
	MailboxManager* mailbox = nullptr;
public:
	/**
	 * @brief Gets EthercatMaster instance.
	 * @returns Pointer to current EthercatMaster object.
	 * @warning Must NOT be called by user!
	*/
	EthercatMaster* GetMaster();
	/**
	 * @brief Gets EthercatDomain instance.
	 * @returns Pointer to current EthercatDomain object.
	 * @warning Must NOT be called by user!
	*/
	EthercatDomain* GetDomain();
	/**
	 * @brief Gets EthercatTimer instance.
	 * @returns Pointer to current EthercatTimer object.
	 * @warning Must NOT be called by user!
	*/
	EthercatTimer* GetTimer();
	/**
	 * @brief Gets EthercatTimer instance.
	 * @returns Pointer to current EthercatSlavesContainer object.
	 * @warning Must NOT be called by user!
	*/
	EthercatSlavesContainer* GetSlaves();
	/**
	 * @brief Gets MailboxManager instance.
	 * @returns Pointer to current MailboxManager object.
	 * @warning Must NOT be called by user!
	*/
	MailboxManager* GetMailbox();
	/**
	 * @brief Registers ethercat master.
	 * @param[in] EthercatMaster* pointer to previously configured
	 * EthercatMaster instance.
	*/	
	void RegisterMaster(EthercatMaster*);
	/**
	 * @brief Registers timer.
	 * @param[in] EthercatTimer* pointer to previously configured
	 * EthercatTimer instance.
	*/	
	void RegisterTimer(EthercatTimer*);
	/**
	 * @brief Register ethercat slaves.
	 * @param[in] EthercatSlavesContainer* pointer to previously configured
	 * EthercatSlavesContainer instance.
	*/
	void RegisterSlavesContainer(EthercatSlavesContainer*);
public:
	EthercatConfiguration();
	~EthercatConfiguration();
	/**
	 * @brief Performs all necessary preparations before
	 * enabling main cycle.
	 * @warning Must NOT be called by user!
	*/
	void Initialize();
	/**
	 * @brief Correctly disables main cycle.
	 * @warning Must NOT be called by user!
	*/
	void Release();
	/**
	 * @brief Performs actions before performing
	 * device tasks in main cycle context.
	 * @warning Must NOT be called by user!
	*/
	void PreProcessingAction();
	/**
	 * @brief Performs actions after performing 
	 * device tasks in main cycle context.
	 * @warning Must NOT be called by user!
	*/
	void PostProcessingAction();
	/**
	 * @brief Updates ethercat telemetry by safe
	 * copying internal telemetry instance
	 * to user telemetry instance.
	*/
	void UpdateEthercatNetworkTelemetry();
	/**
	 * @brief Changes internal instance of ethercat telemerty.
	 * @warning Must NOT be called by user!
	*/
	void ModifyEthercatNetworkTelemetry();	
	/**
	 * @brief Get actual telemetry. Contains data
	 * received with last calling of UpdateEthercatNetworkTelemetry() method.
	 * @returns Pointer to actual telemerty structure.
	 * @see UpdateEthercatNetworkTelemetry().
	*/
	const EthercatNetworkTelemetry* GetTelemetry();
private:
	/**
	 * @brief Get internal telemerty.
	 * @returns Pointer to internal telemerty structure.
	 * @warning Must NOT be called by user!
	*/
	EthercatNetworkTelemetry* GetMasterTelemetry();
	void PrepareMailboxTasks();
};

#endif
