#ifndef ETHERCATSLAVE_H
#define ETHERCATSLAVE_H

#include <map>
#include <string>
#include "coe_object.h"
#include "sync_info.h"
#include "sdo_list.h"
#include "ecrt.h"
#include "coe_drive_state_handler.h"

struct SlaveInfo
{
	std::string name{""};
	uint16_t alias{0};
	uint16_t position{0};
	uint32_t vendor_id{0};
	uint32_t product_code{0};
};

class EthercatSlave
{ 
	SlaveInfo slave_info;	
	ec_slave_config_t* slave_config = nullptr;
	SyncInfo* sync_info = nullptr;
	SDOList* sdo_parameters = nullptr;
	SDOList* sdo_telemetry = nullptr;
	uint32_t assign_activate;
public:
	EthercatSlave() = default;
	virtual ~EthercatSlave();
	
	ec_slave_config_t* GetConfig();
	std::string GetName();
	uint16_t GetAlias();
	uint16_t GetPosition();
	uint32_t GetVendorID();
	uint32_t GetProductCode();
	uint32_t GetAssignActivate();	
	SyncInfo* GetSync();
	SDOList* GetParameterSDO();
	SDOList* GetTelemetrySDO();

	void RegisterSync(SyncInfo*);
	void RegisterParameterSDO(SDOList*);
	void RegisterTelemetrySDO(SDOList*);
	void SetSlaveInfo(std::string, uint16_t, uint16_t, uint32_t, uint32_t);
	void SetAssignActivate(uint32_t);

	CoEObject* GetTxPDOEntry(std::string);
	CoEObject* GetRxPDOEntry(std::string);
	CoEObject* GetParameterSDOEntry(std::string);
	CoEObject* GetTelemetrySDOEntry(std::string);


	void Configure(ec_master_t*);
	void CreatePDO();
	void CreateSDO();
};

#endif