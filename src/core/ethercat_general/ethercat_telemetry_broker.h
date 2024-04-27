/**
 * @brief Service object for ethercat network telemetry operation.
 * Member of EthercatConfiguration.
 * @see EthercatConfiguration, EthercatNetworkTelemetry.
 * @warning Must NOT be created by user!
*/

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
	/**
	 * @brief Wrapper of TelemetryExchanger::UpdateClientTelemetry().
	*/
	void UpdateEthercatTelemetry();
	/**
	 * @brief Changes telemetry fields in interlal telemetry.
	 * @param[in] config Pointer to ethercat configuration for telemetry feilds access. 
	*/
	void ModifyEthercatTelemetry(class EthercatConfiguration* config);
	/**
	 * @brief Wrapper of TelemetryExchanger::UpdateBufferTelemetry().
	*/
	void UpdateEthercatBufferTelemetry();
	/**
	 * @brief Gets user telemetry instance. Wrapper of TelemetryExchanger::GetClientTelemetry().
	 * @returns Pointer to user telemetry instance.
	*/
	const EthercatNetworkTelemetry* GetClientEthercatTelemetry();
	/**
	 * @brief Gets pointer to internal telemetry instance. Wrapper of TelemetryExchanger::GetMasterTelemetry().
	 * @returns Pointer to internal telemetry instance.
	*/
	EthercatNetworkTelemetry* GetMasterEthercatTelemetry();
};

#endif