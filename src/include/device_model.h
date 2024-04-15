#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <iostream>
#include <vector>
#include "subsystem.h"
#include "gantry.h"
#include "accelerator.h"
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

class UnspecifiedDevice : public DeviceModel
{
public:
	void RegisterSubsystem(Subsystem* ext_subsystem);
};

class TorusModel : public DeviceModel
{
	Gantry* gantry;
	Accelerator* accelerator;
public:
	TorusModel();
	~TorusModel();

	void RegisterGantry(Gantry* g);
	void RegisterAccelerator(Accelerator* acc);

	Gantry* GetGantry()	const;
	Accelerator* GetAccelerator() const;
};

#endif

