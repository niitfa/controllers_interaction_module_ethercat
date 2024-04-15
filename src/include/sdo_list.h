#ifndef SDOLIST_H
#define SDOLIST_H

#include "coe_object.h"
#include "ecrt.h"
#include <map>

class SDOList
{
	std::map<std::string, CoEServiceObject*> sdos;
	uint32_t timeout;
public:
	~SDOList();
	void AddObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size, uint64_t value = 0);
	CoEServiceObject* GetObject(std::string);
	void CreateRequests(ec_slave_config_t* slave);
	void SetTimeout(uint32_t timeout);
	std::map<std::string, CoEServiceObject*>* GetMap();	
	void MergeWith(SDOList*);
};

#endif

