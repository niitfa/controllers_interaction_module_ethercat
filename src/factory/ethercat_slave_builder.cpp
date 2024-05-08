#include "ethercat_slave_builder.h"

#include "coe_object_names.h"
#include "ethercat_slave_names.h"
#include "default_sync_info.h"

EthercatSlave* EthercatSlaveBuilder::BuildIOModule(uint16_t alias, uint16_t position)
{
    EthercatSlave* io_module_cn_8033 = new EthercatSlave();
    io_module_cn_8033->SetSlaveInfo(ethercat_slave_names::kIOModuleName, alias, position, 0x00860816, 0x20008033);


	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	DefaultSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

    rxpdo = new PDOEntriesList();
	rxpdo->AddEntry("pdo output", 0xf050, 0x02, 32);

	txpdo = new PDOEntriesList();
	txpdo->AddEntry("pdo input", 0xf050, 0x00, 8);

	sync = new DefaultSyncInfo();
	sync->AddRxPDO(0x1600, rxpdo);	
	sync->AddTxPDO(0x1A00, txpdo);
	sync->Create();

	sdo_parameters = new SDOList();

	sdo_telemetry = new SDOList();
	sdo_telemetry->AddObject("sdo input", 0x1a00, 0x01, 32);
	sdo_telemetry->SetTimeout(500);

	io_module_cn_8033->RegisterSync(sync);
	io_module_cn_8033->RegisterParameterSDO(sdo_parameters);
	io_module_cn_8033->RegisterTelemetrySDO(sdo_telemetry);	
	io_module_cn_8033->SetAssignActivate(0x0300);


    return io_module_cn_8033;
}