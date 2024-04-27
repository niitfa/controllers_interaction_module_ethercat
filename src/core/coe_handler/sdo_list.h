/**
 * @brief Contains CoE object used as SDO. Used for passing in 
 * EthercatSlave while user thread configuring.
 * @details Configuration example:
 * @code
 * #include "sdo_list.h"
 * #include "coe_object_names.h"
 * 
 * void ConfigureSDOList()
 * {
 * 		// Values coe_object_names::kObjectName1...2 should be
 * 		// previously defined in coe_object_names namespace.
 * 		// Using other std::string values as CoE object names is
 * 		// not recommended.
 * 
 * 		SDOList* sdos = new SDOList();
 * 		sdos->AddObject(coe_object_names::kObjectName1, 0x7000, 0x00, 16);
 * 		sdos->AddObject(coe_object_names::kObjectName2, 0x7005, 0x00, 8);
 * 		sdos->SetTimeout(500);
 * }
 * @endcode
 * @see EthercatSlave::RegisterParameterSDO(SDOList*), EthercatSlave::RegisterTelemetrySDO(SDOList*)
*/

#ifndef SDO_LIST_H
#define SDO_LIST_H

#include "coe_service_object.h"
#include "ecrt.h"
#include <map>

class SDOList
{
	std::map<std::string, CoEServiceObject*> sdos;
	uint32_t timeout;
public:
	~SDOList();
	/**
	 * @brief Adds CoE object to list.
	 * @param[in] name Object's name.
	 * @param[in] index Object's index.
	 * @param[in] subindex Object's subindex.
	 * @param[in] size Object's value size in bits.
	 * @param[in] value Object's initial value (for RW objects).
	*/
	void AddObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size, uint64_t value = 0);
	/**
	 * @brief Finds CoEObject by name and gets it's pointer.
	 * @param[in] name Object's name.
	 * @returns Pointer to CoE object with given name if it exists in list, otherwise returns nullptr.
	 * @warning Must NOT be called by user!
	*/
	CoEServiceObject* GetObject(std::string name);
	/**
	 * @brief Configures added SDOs.
	 * @warning Must NOT be called by user!
	*/
	void CreateRequests(ec_slave_config_t* slave);
	/**
	 * @brief Sets SDO timeout.
	 * @param[in] timeout Timeout in milliseconds.
	*/
	void SetTimeout(uint32_t timeout);
	/**
	 * @brief Provides direct access to SDO map.
	 * @returns Pointer to SDO map.
	 * @warning Must NOT be called by user!
	*/
	std::map<std::string, CoEServiceObject*>* GetMap();	
	/**
	 * @brief Inserts SDO map from other SDOList object to current SDOList object's map
	 * @param[in] other Pointer to other sdos.
	 * @warning Must NOT be called by user!
	*/
	void MergeWith(SDOList* other);
};

#endif

