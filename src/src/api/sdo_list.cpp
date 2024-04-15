#include "sdo_list.h"
#include <iostream>

SDOList::~SDOList()
{
	for (auto it = sdos.begin(); it != sdos.end(); ++it)     
	{
		if (it->second) delete it->second;
	}
}

void SDOList::AddObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size, uint64_t value)
{
	CoEServiceObject* obj = new CoEServiceObject(name, index, subindex, size);
	obj->StoreValue(value);
	this->sdos.emplace(obj->GetName(), obj);
}

CoEServiceObject* SDOList::GetObject(std::string name)
{
	if(sdos.find(name) != sdos.end())
	{
		return sdos.find(name)->second;
	}
	return nullptr;
}

std::map<std::string, CoEServiceObject*>* SDOList::GetMap()
{
	return &this->sdos;
}


void SDOList::CreateRequests(ec_slave_config_t* slave)
{
	for (auto it = sdos.begin(); it != sdos.end(); ++it)     
	{
		it->second->CreateSDORequest(slave, timeout);
	}
}

void SDOList::SetTimeout(uint32_t timeout)
{
	this->timeout = timeout;
}

void SDOList::MergeWith(SDOList* other)
{
	this->sdos.insert(other->sdos.begin(), other->sdos.end());
}