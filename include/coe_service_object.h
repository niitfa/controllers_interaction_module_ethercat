/**
 * @brief Derived from CoEObject. Used as slave's SDOs. Contains SDO methods.
 * @warning Must NOT be created by user!
 * @see CoEObject
*/

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
	/**
	 * @brief Creates SDO request.
	 * @param[in] slave_config IgH slave config.
	 * @param[in] timeout_ms SDO timeout in milliseconds.
	*/
	void CreateSDORequest(ec_slave_config_t* slave_config, uint32_t timeout_ms);
	/**
	 * @brief Requests SDO state and transmits stored value to slave if request is successfull.
	 * @returns 1 if request is successfull, 0 otherwise.
	*/
	int WriteTypeRequest();
	/**
	 * @brief Requests SDO state and recieves value from slave if request is successfull.
	 * @returns 1 if request is successfull, 0 otherwise.
	*/
	int ReadTypeRequest();
};

#endif