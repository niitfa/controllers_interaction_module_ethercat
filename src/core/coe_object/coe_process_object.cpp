#include "coe_process_object.h"

CoEProcessObject::CoEProcessObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size)
	: CoEObject{name, index, subindex, size}
{}