#ifndef ETHERCATCONFIGURATION_H
#define ETHERCATCONFIGURATION_H

#include <vector>
#include <map>

#include "ecrt.h"
#include "ethercat_slaves_container.h"
#include "ethercat_master.h"
#include "ethercat_timer.h"
#include "ethercat_domain.h"
#include "ethercat_network_telemetry.h"
#include "mailbox_manager.h"
#include "logger.h"

class EthercatTelemetryBroker;

class EthercatConfiguration
{
	EthercatMaster* master = nullptr;
	EthercatSlavesContainer* slaves = nullptr;	
	EthercatTimer* timer = nullptr;	
	EthercatDomain* domain = nullptr;
	EthercatTelemetryBroker* telemetry_broker = nullptr;
	MailboxManager* mailbox = nullptr;
	Logger logger;
public:
	EthercatMaster* GetMaster();
	EthercatDomain* GetDomain();
	EthercatTimer* GetTimer();
	EthercatSlavesContainer* GetSlaves();
	MailboxManager* GetMailbox();	
	Logger* GetLogger();
	void RegisterMaster(EthercatMaster*);
	void RegisterDomain(EthercatDomain*);
	void RegisterTimer(EthercatTimer*);
	void RegisterSlavesContainer(EthercatSlavesContainer*);
public:
	EthercatConfiguration();
	~EthercatConfiguration();
	void Initialize();
	void Release();
	void PreProcessingAction();
	void PostProcessingAction();
	void UpdateEthercatNetworkTelemetry();
	void ModifyEthercatNetworkTelemetry();	
	const EthercatNetworkTelemetry* GetTelemetry();
private:
	EthercatNetworkTelemetry* GetMasterTelemetry();
};

class EthercatTelemetryBroker
{
	TelemetryExchanger<EthercatNetworkTelemetry>* telemetry_exchanger = new TelemetryExchanger<EthercatNetworkTelemetry>();
public:
	EthercatTelemetryBroker();
	~EthercatTelemetryBroker();
	void UpdateEthercatTelemetry();
	void ModifyEthercatTelemetry(EthercatConfiguration*);
	void UpdateEthercatBufferTelemetry();
	const EthercatNetworkTelemetry* GetClientEthercatTelemetry();
	EthercatNetworkTelemetry* GetMasterEthercatTelemetry();
};

#endif
