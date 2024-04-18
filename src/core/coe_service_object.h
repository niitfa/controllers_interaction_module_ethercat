#ifndef COE_SERVICE_OBJECT_H
#define COE_SERVICE_OBJECT_H

#include <string>
#include "coe_object.h"

class CoEServiceObject : public CoEObject
{
	static const uint32_t kDefaultTimeoutMillisecs = 500;
	ec_sdo_request_t* sdo_request = nullptr;
	uint8_t* sdo_offset;
public:
	CoEServiceObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	void CreateSDORequest(ec_slave_config_t* slave_config, uint32_t timeout_ms);
	int WriteTypeRequest();
	int ReadTypeRequest();
	ec_sdo_request_t* GetSDORequest();
	void CreateSDORequest(ec_sdo_request_t*);
};

#endif