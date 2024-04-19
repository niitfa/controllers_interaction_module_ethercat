#ifndef ETHERCAT_SLAVES_CONTAINER_H
#define ETHERCAT_SLAVES_CONTAINER_H

#include "ethercat_slave.h"
#include "ethercat_master.h"
#include <map>
#include <string>

class EthercatSlavesContainer
{
	std::map<std::string, EthercatSlave*> slaves;
public:
	~EthercatSlavesContainer();
	void RegisterSlave(EthercatSlave*);
	void ConfigureAllSlaves(EthercatMaster*);
	EthercatSlave* GetSlave(std::string);
	uint16_t GetSize();
	std::map<std::string, EthercatSlave*>* GetMap();
	void ReadProcessDataFromDomain();
	void WriteProcessDataToDomain();
};


#endif