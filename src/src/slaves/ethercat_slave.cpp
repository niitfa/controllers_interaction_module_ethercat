#include "ethercat_slave.h"
#include <iostream>

EthercatSlave::~EthercatSlave()
{
	if (sync_info) delete sync_info;
	if (sdo_parameters) delete sdo_parameters;
	if (sdo_telemetry) delete sdo_telemetry;
}

ec_slave_config_t* EthercatSlave::GetConfig() { return this->slave_config; }
std::string EthercatSlave::GetName() { return this->slave_info.name; }
uint16_t EthercatSlave::GetAlias() { return this->slave_info.alias; }
uint16_t EthercatSlave::GetPosition() { return this->slave_info.position; }
uint32_t EthercatSlave::GetVendorID() { return this->slave_info.vendor_id; }
uint32_t EthercatSlave::GetProductCode() { return this->slave_info.product_code; }
uint32_t EthercatSlave::GetAssignActivate() { return this->assign_activate; }
SDOList* EthercatSlave::GetParameterSDO() { return this->sdo_parameters; }
SDOList* EthercatSlave::GetTelemetrySDO() { return this->sdo_telemetry; }

SyncInfo* EthercatSlave::GetSync() { return this->sync_info; }
void EthercatSlave::RegisterSync(SyncInfo* sync) { this->sync_info = sync; }
void EthercatSlave::RegisterParameterSDO(SDOList* sdo) { this->sdo_parameters = sdo; }
void EthercatSlave::RegisterTelemetrySDO(SDOList* sdo) { this->sdo_telemetry = sdo; }


void EthercatSlave::SetSlaveInfo(
	std::string name, 
	uint16_t alias, 
	uint16_t position, 
	uint32_t vendor_id, 
	uint32_t product_code)
{
	this->slave_info.name = name;
	this->slave_info.alias = alias;	
	this->slave_info.position = position;	
	this->slave_info.vendor_id = vendor_id;	
	this->slave_info.product_code = product_code;		
}

void EthercatSlave::SetAssignActivate(uint32_t assign_activate)
{
	this->assign_activate = assign_activate;
}

CoEObject* EthercatSlave::GetTxPDOEntry(std::string obj_name)
{
	CoEObject* obj = this->sync_info->GetTxPDO()->GetEntry(obj_name);
	if (!obj) 
	{
		std::cerr << ">>> Ethercat: error. Can't find registered TxPDO entry \""
		<< obj_name << "\" for slave \"" << this->slave_info.name << "\".\n";
	}
	return obj;		
}

CoEObject* EthercatSlave::GetRxPDOEntry(std::string obj_name)
{
	CoEObject* obj = this->sync_info->GetRxPDO()->GetEntry(obj_name);
	if (!obj) 
	{
		std::cerr << ">>> Ethercat: error. Can't find registered RxPDO entry \""
		<< obj_name << "\" for slave \"" << this->slave_info.name << "\".\n";
	}
	return obj;		
}

CoEObject* EthercatSlave::GetParameterSDOEntry(std::string obj_name)
{
	CoEObject* obj = this->sdo_parameters->GetObject(obj_name);
	if(!obj)
	{
		std::cerr << ">>> Ethercat: error. Can't find registered SDO entry \""
		<< obj_name << "\" for slave \"" << this->slave_info.name << "\".\n";		
	}
	return obj;
}

CoEObject* EthercatSlave::GetTelemetrySDOEntry(std::string obj_name)
{
	CoEObject* obj = this->sdo_telemetry->GetObject(obj_name);
	if(!obj)
	{
		std::cerr << ">>> Ethercat: error. Can't find registered SDO entry \""
		<< obj_name << "\" for slave \"" << this->slave_info.name << "\".\n";		
	}
	return obj;
}



void EthercatSlave::Configure(ec_master_t* master)
{
	this->slave_config = ecrt_master_slave_config(
		master,
		this->slave_info.alias,
		this->slave_info.position,
		this->slave_info.vendor_id,
		this->slave_info.product_code
		);

	if(!slave_config)
	{
		std::cerr << ">>> Ethercat: " << "can't configure slave "
		<< this->slave_info.position << " \"" << this->slave_info.name << "\"\n";
	}
	else
	{
		std::cerr << ">>> Ethercat: " << "slave "
	 	<< this->slave_info.position << " \"" << this->slave_info.name << "\" is configured.\n";
	}
}

void EthercatSlave::CreatePDO()
{
	if (ecrt_slave_config_pdos(slave_config, EC_END, sync_info->GetSyncs()))
	{
        std::cerr << ">>> Ethercat: " << "Failed to configure PDOs for slave " 
        << this->slave_info.position << " \"" << this->slave_info.name << "\"\n";
    }
    else
    {
    	std::cerr << ">>> Ethercat: " << "PDO entries for slave " 
        << this->slave_info.position << " \"" << this->slave_info.name << "\"" 
        <<" are configured.\n";
    }

}

void EthercatSlave::CreateSDO()
{
	if (sdo_parameters) sdo_parameters->CreateRequests(this->slave_config);
	if (sdo_telemetry) sdo_telemetry->CreateRequests(this->slave_config);	
}	