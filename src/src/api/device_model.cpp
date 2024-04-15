#include "device_model.h"

// DeviceModel
DeviceModel::~DeviceModel()
{
	delete ethercat_config;
	for (auto it = DeviceModel::GetSubsystemContainer()->begin(); it != DeviceModel::GetSubsystemContainer()->end(); ++it)
	{
		if (*it) delete (*it);
	}
}
void DeviceModel::Action()
{
	if (ethercat_config)
	{
		ethercat_config->ModifyEthercatNetworkTelemetry();
	}

	for (auto it = DeviceModel::GetSubsystemContainer()->begin(); it != DeviceModel::GetSubsystemContainer()->end(); ++it)
	{
		(*it)->Action();
		(*it)->ModifyTelemetry();
	}
}

void DeviceModel::RegisterEthercatConfig(EthercatConfiguration* cfg)
{
	/* Must de called after all subsystem registrations */
	this->ethercat_config = cfg;
	for (auto it = DeviceModel::GetSubsystemContainer()->begin(); it != DeviceModel::GetSubsystemContainer()->end(); ++it)
	{
		(*it)->PassEthercatConfig(cfg);
	}
}

EthercatConfiguration* DeviceModel::GetEthercatConfig()
{
	return this->ethercat_config;
}

void DeviceModel::UpdateTelemetry()
{
	if(ethercat_config)
	{
		ethercat_config->UpdateEthercatNetworkTelemetry();
	}

	for (auto it = DeviceModel::GetSubsystemContainer()->begin(); it != DeviceModel::GetSubsystemContainer()->end(); ++it)
	{
		(*it)->UpdateSubsystemTelemetry();
	}
}

void DeviceModel::RegisterSubsystem(Subsystem* ext_subsystem, Subsystem** p_int_subsystem)
{
	if (!*p_int_subsystem)
	{
		*p_int_subsystem = ext_subsystem;
		this->vec_subsystems.push_back(*p_int_subsystem);
	}
}

std::vector<Subsystem*>* DeviceModel::GetSubsystemContainer()
{
	return &vec_subsystems;
}

// UnspecifiedDevice

void UnspecifiedDevice::RegisterSubsystem(Subsystem* ext_subsystem)
{
	Subsystem* plug_pointer = nullptr;
	DeviceModel::RegisterSubsystem(ext_subsystem, &plug_pointer);
}

// TorusModel
TorusModel::TorusModel() = default;

TorusModel::~TorusModel() = default;

void TorusModel::RegisterGantry(Gantry* g)
{
	this->DeviceModel::RegisterSubsystem(g, (Subsystem**)&gantry);
}

void TorusModel::RegisterAccelerator(Accelerator* acc)
{
	this->DeviceModel::RegisterSubsystem(acc, (Subsystem**)&accelerator);
}

Gantry* TorusModel::GetGantry() const
{
	return this->gantry;
}

Accelerator* TorusModel::GetAccelerator() const 
{
	return this->accelerator;
}
