#include "coe_service_object.h"

CoEServiceObject::CoEServiceObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size)
	: CoEObject(name, index, subindex, size)
{
	 sdo_request = nullptr;
}	

void CoEServiceObject::CreateSDORequest(ec_slave_config_t* slave_config, uint32_t timeout_ms = kDefaultTimeoutMillisecs)
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
        /* fault reaction */
	}

	ecrt_sdo_request_timeout(sdo_request, timeout_ms);
	this->sdo_offset = ecrt_sdo_request_data(sdo_request);
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

	return request_is_successful;	
}