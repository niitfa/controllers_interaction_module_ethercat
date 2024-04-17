#include "coe_object.h"
#include <iostream>

#include <bitset>
#include "word_bit.h"
		//std::bitset<64> y(it->second->LoadValue());
		//std::cout << it->second->GetName() << " read: " << y << std::endl;

/* CoEObject */
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

	//std::cout <<  byte_position/**(uint64_t *)(domain_offset + byte_position) */<< std::endl;
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

/* CoEProcessObject */
CoEProcessObject::CoEProcessObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size)
	: CoEObject{name, index, subindex, size}
{}

/* CoEServiceObject */
CoEServiceObject::CoEServiceObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size)
	: CoEObject(name, index, subindex, size)
{
	 sdo_request = nullptr;
}	

void CoEServiceObject::CreateSDORequest(ec_slave_config_t* slave_config, uint32_t timeout_ms = DEFAULT_TIMEOUT_MS)
{
	uint16_t bits_per_byte 		= 8;
	uint16_t min_sdo_size_bytes = 1;
	uint16_t sdo_size_bytes = this->GetSizeBit() / bits_per_byte;

	this->sdo_request = ecrt_slave_config_create_sdo_request(
		slave_config, 
		this->GetIndex(), 
		this->GetSubindex(), 
		std::max(sdo_size_bytes, min_sdo_size_bytes)
		);

	if(!sdo_request)
	{
		// error log
		// logger->Add("Error creating sdo request");
		//std::cout << "ERROR SDO CREATE\n";
	}

	ecrt_sdo_request_timeout(sdo_request, timeout_ms);
	this->sdo_offset = ecrt_sdo_request_data(sdo_request);

	/* debug */
	//std::cout << "SDO create: " << std::hex << GetIndex()<< " " << GetSubindex() << " " << GetName() << std::dec << "\n";
}

int CoEServiceObject::WriteTypeRequest()
{
	int request_is_successful = (ecrt_sdo_request_state(sdo_request) == EC_REQUEST_SUCCESS);
	ecrt_sdo_request_write(sdo_request);

	CoEObject::ec_write_le(
		this->sdo_offset, 
		0, 
		0, 
		this->LoadValue(),
		this->GetSizeBit()
		);
	return request_is_successful;
}

int CoEServiceObject::ReadTypeRequest()
{
	int request_is_successful = (ecrt_sdo_request_state(sdo_request) == EC_REQUEST_SUCCESS);
	ecrt_sdo_request_read(sdo_request);
	int64_t val = CoEObject::ec_read_le(
		this->sdo_offset, 
		0, 
		0, 
		this->GetSizeBit()
		);
	CoEObject::StoreValue(val);

	/*if (ecrt_sdo_request_state(sdo_request) == EC_REQUEST_SUCCESS)
	{
		std::cerr << "SDO SUCCESS\n";
	}
	if(ecrt_sdo_request_state(sdo_request) == EC_REQUEST_BUSY)
	{
		std::cerr << "SDO BUSY\n";
	}
	if(ecrt_sdo_request_state(sdo_request) == EC_REQUEST_UNUSED)
	{
		std::cerr << "SDO UNUSED\n";
	}
	if(ecrt_sdo_request_state(sdo_request) == EC_REQUEST_ERROR)
	{
		std::cerr << "SDO ERROR\n";
	} */

	return request_is_successful;	
}

ec_sdo_request_t* CoEServiceObject::GetSDORequest() { return this->sdo_request; }
