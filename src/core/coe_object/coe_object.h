#ifndef COE_OBJECT_H
#define COE_OBJECT_H

#include <string>
#include "ecrt.h"

class CoEObject
{
	std::string name;
	uint16_t index;
	uint8_t subindex;
	uint16_t size;
	int64_t value;

	uint8_t* domain_offset;
	uint16_t byte_position;
	uint8_t bit_position;

public:
	CoEObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	std::string GetName();
	uint16_t GetIndex();
	uint8_t GetSubindex();
	uint8_t GetSizeBit();

	void RegisterDomainOffset(uint8_t* domain_offset);
	void RegisterBytePosition(uint16_t byte_position);
	void RegisterBitPosition(uint8_t bit_position);

	int64_t LoadValue();
	void StoreValue(int64_t);

	void WriteValueToFrame(); 
	void ReadValueFromFrame();	

protected:
	int64_t ec_read_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, uint8_t qBits);
	void ec_write_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, int64_t data, uint8_t qBits);
};

#endif