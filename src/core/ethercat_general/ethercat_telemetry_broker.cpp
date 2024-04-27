#include "ethercat_configuration.h"

EthercatTelemetryBroker::EthercatTelemetryBroker() = default;

EthercatTelemetryBroker::~EthercatTelemetryBroker()
{
	delete telemetry_exchanger;
}

void EthercatTelemetryBroker::UpdateEthercatTelemetry()
{
	telemetry_exchanger->UpdateClientTelemetry();
}

void EthercatTelemetryBroker::UpdateEthercatBufferTelemetry()
{
	telemetry_exchanger->UpdateBufferTelemetry();
}

const EthercatNetworkTelemetry* EthercatTelemetryBroker::GetClientEthercatTelemetry()
{
	return telemetry_exchanger->GetClientTelemetry();
}

EthercatNetworkTelemetry* EthercatTelemetryBroker::GetMasterEthercatTelemetry()
{
	return telemetry_exchanger->GetMasterTelemetry();
}

void EthercatTelemetryBroker::ModifyEthercatTelemetry(EthercatConfiguration* ethercat_config)
{
	auto modified_telemetry = telemetry_exchanger->GetMasterTelemetry();

	ecrt_master_state(ethercat_config->GetMaster()->GetRequest(), &(modified_telemetry->master_state));

	modified_telemetry->slaves_info.clear();
	uint16_t slaves_responding = modified_telemetry->master_state.slaves_responding;
	for (int i = 0; i < slaves_responding; ++i)
	{
		modified_telemetry->slaves_info.push_back({});
		ecrt_master_get_slave(ethercat_config->GetMaster()->GetRequest(), i, &(modified_telemetry->slaves_info.back()));
	}
}

