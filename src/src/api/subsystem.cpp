#include "subsystem.h"

Subsystem::Subsystem()
{}

Subsystem::~Subsystem()
{}

EthercatConfiguration* Subsystem::GetEthercatConfig()
{
	return this->ethercat_config;
}
void Subsystem::PassEthercatConfig(EthercatConfiguration* cfg)
{
	if(cfg)
	{
		this->ethercat_config = cfg;
	}
}