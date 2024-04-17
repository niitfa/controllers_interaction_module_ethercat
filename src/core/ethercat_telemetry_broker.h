#ifndef ETHERCAT_TELEMETRY_BROKER_H
#define ETHERCAT_TELEMETRY_BROKER_H

#include "telemetry_exchanger.h"
#include "ethercat_network_telemetry.h"

class EthercatTelemetryBroker
{
	TelemetryExchanger<EthercatNetworkTelemetry>* telemetry_exchanger = new TelemetryExchanger<EthercatNetworkTelemetry>();
public:
	EthercatTelemetryBroker();
	~EthercatTelemetryBroker();
	void UpdateEthercatTelemetry();
	void ModifyEthercatTelemetry(class EthercatConfiguration*);
	void UpdateEthercatBufferTelemetry();
	const EthercatNetworkTelemetry* GetClientEthercatTelemetry();
	EthercatNetworkTelemetry* GetMasterEthercatTelemetry();
};

#endif