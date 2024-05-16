#include "ethercat_slave_builder.h"
#include "coe_object_names.h"
#include "ethercat_slave_names.h"
#include "advanced_sync_info.h"

EthercatSlave* EthercatSlaveBuilder::BuildIOModule(uint16_t alias, uint16_t position)
{
    EthercatSlave* io_module_cn_8033 = new EthercatSlave();
    io_module_cn_8033->SetSlaveInfo(ethercat_slave_names::kIOModuleName, alias, position, 0x00860816, 0x20008033);

	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	/* CT-3168 */
	txpdo = new PDOEntriesList();
	txpdo->AddEntry("Ch#1", 0x6001, 0x01, 16);
	txpdo->AddEntry("Ch#2", 0x6001, 0x02, 16);
	txpdo->AddEntry("Ch#3", 0x6001, 0x03, 16);
	txpdo->AddEntry("Ch#4", 0x6001, 0x04, 16);
	txpdo->AddEntry("Ch#5", 0x6001, 0x05, 16);
	txpdo->AddEntry("Ch#6", 0x6001, 0x06, 16);
	txpdo->AddEntry("Ch#7", 0x6001, 0x07, 16);
	txpdo->AddEntry("Ch#8", 0x6001, 0x08, 16);

	/* CT-623f */
	/*txpdo = new PDOEntriesList();
	txpdo->AddEntry("Ch#1", 0x6000, 0x01, 1);
	txpdo->AddEntry("Ch#2", 0x6000, 0x02, 1);
	txpdo->AddEntry("Ch#3", 0x6000, 0x03, 1);
	txpdo->AddEntry("Ch#4", 0x6000, 0x04, 1);
	txpdo->AddEntry("Ch#5", 0x6000, 0x05, 1);
	txpdo->AddEntry("Ch#6", 0x6000, 0x06, 1);
	txpdo->AddEntry("Ch#7", 0x6000, 0x07, 1);
	txpdo->AddEntry("Ch#8", 0x6000, 0x08, 1);

	rxpdo = new PDOEntriesList();
	rxpdo->AddEntry("Ch#1", 0x7000, 0x01, 1);
	rxpdo->AddEntry("Ch#2", 0x7000, 0x02, 1);
	rxpdo->AddEntry("Ch#3", 0x7000, 0x03, 1);
	rxpdo->AddEntry("Ch#4", 0x7000, 0x04, 1);
	rxpdo->AddEntry("Ch#5", 0x7000, 0x05, 1);
	rxpdo->AddEntry("Ch#6", 0x7000, 0x06, 1);
	rxpdo->AddEntry("Ch#7", 0x7000, 0x07, 1);
	rxpdo->AddEntry("Ch#8", 0x7000, 0x08, 1); */

	sync = new AdvancedSyncInfo();
	//sync->AddRxPDO(0x1600, rxpdo);
	sync->AddTxPDO(0x1A00, txpdo);
	sync->DisableSM2();
	//sync->DisableSM3();
	sync->Create();

	sdo_parameters = new SDOList();
	//sdo_parameters->AddObject("sdo input", 0x1c13, 0x01, 16, 0x1A00);

	sdo_telemetry = new SDOList();
	sdo_telemetry->AddObject("sdo input", 0xf050, 0x00, 8);
	sdo_telemetry->SetTimeout(500);

	io_module_cn_8033->RegisterSync(sync);
	//io_module_cn_8033->RegisterParameterSDO(sdo_parameters);
	io_module_cn_8033->RegisterTelemetrySDO(sdo_telemetry);	
	//io_module_cn_8033->SetAssignActivate(0x0300);

    return io_module_cn_8033;
}