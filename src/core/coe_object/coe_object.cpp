#include <iostream>
#include <bitset>
#include "word_bit.h"
#include "coe_object.h"

CoEObject::CoEObject(std::string nm, uint16_t ind, uint8_t si, uint16_t sz) : 
	name{nm},
	index{ind},
	subindex{si},
	size{sz} 
{}

std::string CoEObject::GetName() 				{ return this->name; }
uint16_t 	CoEObject::GetIndex()				{ return this->index; }
uint8_t 	CoEObject::GetSubindex()			{ return this->subindex; }
uint8_t 	CoEObject::GetSizeBit()				{ return this->size; }
int64_t 	CoEObject::LoadValue() 				{ return this->value; }
void 		CoEObject::StoreValue(int64_t val) 	{ this->value = val; }

void CoEObject::ReadValueFromFrame()
{
	this->value = ec_read_le(
		this->domain_offset, 
		this->byte_position, 
		this->bit_position, 
		this->GetSizeBit()
		);
}
void CoEObject::WriteValueToFrame() 
{
	ec_write_le(
		this->domain_offset, 
		this->byte_position, 
		this->bit_position, 
		this->LoadValue(),
		this->GetSizeBit()
		);
}

int64_t* CoEObject::GetValueAddress()
{
	return &this->value;
}


void CoEObject::RegisterDomainOffset(uint8_t* domain_offset)
{
	this->domain_offset = domain_offset;
}
void CoEObject::RegisterBytePosition(uint16_t byte_position)
{
	this->byte_position = byte_position;
}
void CoEObject::RegisterBitPosition(uint8_t bit_position)
{
	this->bit_position = bit_position;
}

int64_t CoEObject::ec_read_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, uint8_t qBits)
{
	int64_t bitsPayload = *(int64_t*)(pBitsArray + bytePos);
	int64_t result = ((bitsPayload >> bitPos) & (((int64_t)1 << qBits) - 1));
	
	// Заполняем старшие биты 0 или 1 в зависимости от знака
	uint8_t sign_bit = WordBit::Read(&result, GetSizeBit() - 1);
	for(int bit_no = GetSizeBit(); bit_no != sizeof(result)*8; ++bit_no)
	{
		WordBit::Write(&result, bit_no, sign_bit);
	}
	return result;
}

void CoEObject::ec_write_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, int64_t data, uint8_t qBits)
{
	int64_t* pBitsPayload = (int64_t*)(pBitsArray + bytePos);
	int64_t mask32 = ((int64_t)1 << qBits) - 1;
	int64_t mask64 = ~(mask32 << bitPos);
	*pBitsPayload &= mask64;
	*pBitsPayload |= ((data & mask32) << bitPos);
}
