#ifndef COE_PROCESS_OBJECT_H
#define COE_PROCESS_OBJECT_H

#include <string>
#include "coe_object.h"

class CoEProcessObject : public CoEObject
{
public:
	CoEProcessObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
};

#endif