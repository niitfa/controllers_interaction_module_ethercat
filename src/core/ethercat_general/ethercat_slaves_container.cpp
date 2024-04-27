#include "ethercat_slaves_container.h"
#include "ecrt.h"

EthercatSlavesContainer::~EthercatSlavesContainer()
{
	for (auto it = this->slaves.begin(); it != this->slaves.end(); ++it)
	{
		if (it->second) delete it->second;
	}
}

void EthercatSlavesContainer::RegisterSlave(EthercatSlave* slave)
{
	slaves.emplace(slave->GetName(), slave);
}

void EthercatSlavesContainer::ConfigureAllSlaves(EthercatMaster* master)
{
	for (auto it = this->slaves.begin(); it!= this->slaves.end(); ++it)
	{
		it->second->Configure(master->GetRequest());
		it->second->CreatePDO();
		it->second->CreateSDO();
	}
}

EthercatSlave* EthercatSlavesContainer::GetSlave(std::string name)
{
	if(slaves.find(name) != slaves.end())
	{
		return slaves.find(name)->second;
	}
	return nullptr;
}

uint16_t EthercatSlavesContainer::GetSize()
{
	return slaves.size();
}

std::map<std::string, EthercatSlave*>* EthercatSlavesContainer::GetMap()
{
	return &this->slaves;
}

void EthercatSlavesContainer::ReadProcessDataFromDomain()
{
	for(auto it = slaves.begin(); it != slaves.end(); ++it)
	{
		auto rxpdo_map = it->second->GetSync()->GetRxPDO()->GetMap();
		auto txpdo_map = it->second->GetSync()->GetTxPDO()->GetMap();

		for (auto it_pdo = rxpdo_map->begin(); it_pdo != rxpdo_map->end(); ++it_pdo)
		{
	
			it_pdo->second->ReadValueFromFrame();
		}

		for (auto it_pdo = txpdo_map->begin(); it_pdo != txpdo_map->end(); ++it_pdo)
		{
			it_pdo->second->ReadValueFromFrame();
		}
	}
}
void EthercatSlavesContainer::WriteProcessDataToDomain()
{
	for(auto it = slaves.begin(); it != slaves.end(); ++it)
	{
		auto rxpdo_map = it->second->GetSync()->GetRxPDO()->GetMap();
		for (auto it_pdo = rxpdo_map->begin(); it_pdo != rxpdo_map->end(); ++it_pdo)
		{
			it_pdo->second->WriteValueToFrame();
		}
	}
}