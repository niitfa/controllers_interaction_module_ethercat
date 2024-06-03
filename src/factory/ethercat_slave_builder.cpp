#include "ethercat_slave_builder.h"
#include "coe_object_names.h"
#include "ethercat_slave_names.h"
#include "advanced_sync_info.h"
#include "default_sync_info.h"
#include "ecrt.h"

using namespace coe_object_names;
using namespace ethercat_slave_names;

EthercatSlave* EthercatSlaveBuilder::BuildIOModule(uint16_t alias, uint16_t position)
{
    EthercatSlave* io_module_cn_8033 = new EthercatSlave();
    io_module_cn_8033->SetSlaveInfo(kIOModuleName, alias, position, 0x00860816, 0x20008033);
	//io_module_cn_8033->AddInitialSDOEntry("Synchronization type 0", 0x1c32, 0x01, 16, 2);
	//io_module_cn_8033->AddInitialSDOEntry("Synchronization type 1", 0x1c33, 0x01, 16, 2);

	//io_module_cn_8033->AddInitialSDOEntry("Get cycle time 0", 0x1c32, 0x08, 32, 1000);
	//io_module_cn_8033->AddInitialSDOEntry("Get cycle time 1", 0x1c33, 0x08, 32, 1000);

	//io_module_cn_8033->AddInitialSDOEntry("Sync0 cycle time", 0x1c32, 0x0a, 32, 1000000);
	//io_module_cn_8033->AddInitialSDOEntry("Sync1 cycle time", 0x1c33, 0x0a, 32, 1000000);

	AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	/* CT-3168 */
	PDOEntriesList* txpdo_ct_3168 = new PDOEntriesList();
	txpdo_ct_3168->AddEntry(kCT3168_AI0, 0x6001, 0x01, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI1, 0x6001, 0x02, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI2, 0x6001, 0x03, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI3, 0x6001, 0x04, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI4, 0x6001, 0x05, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI5, 0x6001, 0x06, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI6, 0x6001, 0x07, 16);
	txpdo_ct_3168->AddEntry(kCT3168_AI7, 0x6001, 0x08, 16);

	/* CT-623f */
	PDOEntriesList* txpdo_ct_623f = new PDOEntriesList();
	txpdo_ct_623f->AddEntry(kCT632F_DI0, 0x6002, 0x01, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI1, 0x6002, 0x02, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI2, 0x6002, 0x03, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI3, 0x6002, 0x04, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI4, 0x6002, 0x05, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI5, 0x6002, 0x06, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI6, 0x6002, 0x07, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI7, 0x6002, 0x08, 1);

	PDOEntriesList* rxpdo_ct_623f = new PDOEntriesList();
	rxpdo_ct_623f->AddEntry(kCT632F_DO0, 0x7002, 0x01, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO1, 0x7002, 0x02, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO2, 0x7002, 0x03, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO3, 0x7002, 0x04, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO4, 0x7002, 0x05, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO5, 0x7002, 0x06, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO6, 0x7002, 0x07, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO7, 0x7002, 0x08, 1);

	sync = new AdvancedSyncInfo();
	
	sync->AddTxPDO(0x1A00, txpdo_ct_3168); /* CT-3168 */
	sync->AddRxPDO(0x1600, rxpdo_ct_623f); /* CT-623f */
	sync->AddTxPDO(0x1A01, txpdo_ct_623f);
	sync->Create();

	sdo_parameters = new SDOList();
	//sdo_parameters->AddObject("sdo input", 0x1c13, 0x01, 16, 0x1A00);

	sdo_telemetry = new SDOList();
	//sdo_telemetry->AddObject("Sync0 cycle time", 0x1c32, 0x0a, 32);
	//sdo_telemetry->AddObject("Sync1 cycle time", 0x1c33, 0x0a, 32);
	sdo_telemetry->SetTimeout(500);

	io_module_cn_8033->RegisterSync(sync);
	//io_module_cn_8033->RegisterParameterSDO(sdo_parameters);
	io_module_cn_8033->RegisterTelemetrySDO(sdo_telemetry);	
	//io_module_cn_8033->SetAssignActivate(0x0000);

	//ecrt_slave_config_sdo32(io_module_cn_8033->GetConfig(), 0x1c32, 0x0a, 1000);


    return io_module_cn_8033;
}

EthercatSlave* EthercatSlaveBuilder::BuildKVFilterDrive(uint16_t alias, uint16_t position)
{
	EthercatSlave* kv_filter_drive = new EthercatSlave();

	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	kv_filter_drive->SetSlaveInfo(kKVFilterDriveName, alias, position, 0x00004321, 0x00008600);

	rxpdo = new PDOEntriesList();
	rxpdo->AddEntry(kControlword, 0x6040, 0x00, 16);
	rxpdo->AddEntry(kModeOfOperation, 0x6060, 0x00, 8);
	rxpdo->AddEntry(kTargetPosition, 0x607A, 0x00, 32);
	rxpdo->AddEntry(kProfileVelocity, 0x60FF, 0x00, 32);

	txpdo = new PDOEntriesList();
	txpdo->AddEntry(kStatusword, 0x6041, 0x00, 16);
	txpdo->AddEntry(kModeOfOperationOut, 0x6061, 0x00, 8);
	txpdo->AddEntry(kActualPosition, 0x6064, 0x00, 32);
	txpdo->AddEntry(kActualVelocity, 0x606C, 0x00, 32);

	sync = new AdvancedSyncInfo();
	sync->AddRxPDO(0x1600, rxpdo);	
	sync->AddTxPDO(0x1A00, txpdo);
	sync->Create();

	sdo_parameters = new SDOList();
	sdo_parameters->AddObject(kPeakCurrent, 0x2000, 0x00, 32, 1000);
	sdo_parameters->AddObject(kMicrostepResolution, 0x2001, 0x00, 32, 200);
	sdo_parameters->AddObject(kMaxProfileVelocity, 0x6081, 0x00, 32, 5000);
	sdo_parameters->AddObject(kProfileAcceleration, 0x6083, 0x00, 32, 20000);
	sdo_parameters->AddObject(kProfileDeceleration, 0x6084, 0x00, 32, 20000);
	sdo_parameters->SetTimeout(500);

	sdo_telemetry = new SDOList();
	sdo_telemetry->AddObject("Synchronization type 0", 	0x1c32, 0x01, 16);
	sdo_telemetry->AddObject("Cycle time 0", 			0x1c32, 0x02, 32);
	sdo_telemetry->AddObject("Output shift time 0", 	0x1c32, 0x03, 32);
	sdo_telemetry->AddObject("Calc and copy time 0", 	0x1c32, 0x06, 32);
	sdo_telemetry->AddObject("Delay time 0", 			0x1c32, 0x09, 32);

	sdo_telemetry->AddObject("Synchronization type 1", 	0x1c33, 0x01, 16);
	sdo_telemetry->AddObject("Cycle time 1", 			0x1c33, 0x02, 32);
	sdo_telemetry->AddObject("Input shift time 1", 		0x1c33, 0x03, 32);
	sdo_telemetry->AddObject("Calc and copy time 1", 	0x1c33, 0x06, 32);
	sdo_telemetry->AddObject("Delay time 1", 			0x1c33, 0x09, 32);
	sdo_telemetry->SetTimeout(500);

	kv_filter_drive->RegisterSync(sync);
	kv_filter_drive->RegisterParameterSDO(sdo_parameters);
	kv_filter_drive->RegisterTelemetrySDO(sdo_telemetry);	

	return kv_filter_drive;
}

EthercatSlave* EthercatSlaveBuilder::BuildKVDetectorDrive(uint16_t alias, uint16_t position)
{
	EthercatSlave* kv_detector_drive = new EthercatSlave();

	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	kv_detector_drive->SetSlaveInfo(kKVDetectorDriveName, alias, position, 0x00004321, 0x00008600);

	rxpdo = new PDOEntriesList();
	rxpdo->AddEntry(kControlword, 0x6040, 0x00, 16);
	rxpdo->AddEntry(kModeOfOperation, 0x6060, 0x00, 8);
	rxpdo->AddEntry(kTargetPosition, 0x607A, 0x00, 32);
	rxpdo->AddEntry(kProfileVelocity, 0x60FF, 0x00, 32);

	txpdo = new PDOEntriesList();
	txpdo->AddEntry(kStatusword, 0x6041, 0x00, 16);
	txpdo->AddEntry(kModeOfOperationOut, 0x6061, 0x00, 8);
	txpdo->AddEntry(kActualPosition, 0x6064, 0x00, 32);
	txpdo->AddEntry(kActualVelocity, 0x606C, 0x00, 32);

	sync = new AdvancedSyncInfo();
	sync->AddRxPDO(0x1600, rxpdo);	
	sync->AddTxPDO(0x1A00, txpdo);
	sync->Create();

	sdo_parameters = new SDOList();
	sdo_parameters->AddObject(kPeakCurrent, 0x2000, 0x00, 32, 1000);
	sdo_parameters->AddObject(kMicrostepResolution, 0x2001, 0x00, 32, 200);
	sdo_parameters->AddObject(kMaxProfileVelocity, 0x6081, 0x00, 32, 5000);
	sdo_parameters->AddObject(kProfileAcceleration, 0x6083, 0x00, 32, 20000);
	sdo_parameters->AddObject(kProfileDeceleration, 0x6084, 0x00, 32, 20000);
	sdo_parameters->SetTimeout(500);

	kv_detector_drive->RegisterSync(sync);
	kv_detector_drive->RegisterParameterSDO(sdo_parameters);
	//kv_filter_drive->SetAssignActivate(0x0300);
	//kv_filter_drive->RegisterTelemetrySDO(sdo_telemetry);	

	return kv_detector_drive;
}