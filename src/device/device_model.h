#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <iostream>
#include <vector>
#include "subsystem.h"
#include "ethercat_configuration.h"

class DeviceModel
{
	std::vector<Subsystem*> vec_subsystems;
	EthercatConfiguration* ethercat_config = nullptr;
public:
	virtual ~DeviceModel();
	void Action();
	void RegisterEthercatConfig(EthercatConfiguration*);
	EthercatConfiguration* GetEthercatConfig();
	void UpdateTelemetry();
protected:
	void RegisterSubsystem(Subsystem* ext_subsystem, Subsystem** p_int_subsystem);
	std::vector<Subsystem*>* GetSubsystemContainer();
};

#endif

