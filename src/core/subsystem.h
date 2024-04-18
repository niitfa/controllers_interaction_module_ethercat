#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <vector>
#include "ethercat_configuration.h"
#include "external_emulation_manager.h"
#include "emulated_event_content_creator.h"

class Subsystem
{
	EthercatConfiguration* ethercat_config = nullptr;
public:
	Subsystem();
	virtual ~Subsystem();
	virtual void Action() = 0;
	virtual void UpdateSubsystemTelemetry() = 0;
	virtual void ModifyTelemetry() = 0;
	EthercatConfiguration* GetEthercatConfig();
	void PassEthercatConfig(EthercatConfiguration*);
};

#endif // !SUBSYSTEM_H



