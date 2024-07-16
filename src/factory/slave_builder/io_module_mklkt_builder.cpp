#include "io_module_mklkt_builder.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"
#include "advanced_sync_info.h"
#include "sdo_list.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

EthercatSlave* IOModuleMKLKTBuilder::Build(uint16_t alias, uint16_t position)
{
    int drive_counts_per_round = 8388608; // 23-разрядный двигатель

    EthercatSlave* ecat_io_module = new EthercatSlave();

    ecat_io_module->SetSlaveInfo(kIOModuleName, alias, position, 0x00860816, 0x20008033);

    AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

    /* Уточнить список после получение инф. о модели драйвера*/

    PDOEntriesList* txpdo_ct_5122 = new PDOEntriesList();
    txpdo_ct_5122->AddEntry(kCT5122_CH0_IDLE,       0x6000, 0x01, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH0_Data,       0x6000, 0x02, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH0_Enc_UP,     0x6000, 0x03, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH0_Enc_DOWN,   0x6000, 0x04, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_IDLE,       0x6000, 0x06, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_Data,       0x6000, 0x07, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_Enc_UP,     0x6000, 0x08, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_Enc_DOWN,   0x6000, 0x09, 1);
    txpdo_ct_5122->AddEntry(kCT5122_CH0_Counter_Val, 0x6000, 0x0B, 32);
    txpdo_ct_5122->AddEntry(kCT5122_CH0_Capture_Val, 0x6000, 0x0C, 32);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_Counter_Val, 0x6000, 0x0D, 32);
    txpdo_ct_5122->AddEntry(kCT5122_CH1_Capture_Val, 0x6000, 0x0E, 32);


    PDOEntriesList* rxpdo_ct_5122 = new PDOEntriesList();
    rxpdo_ct_5122->AddEntry(kCT5122_CH0_Output_Control, 0x7000, 0x01, 1);
    rxpdo_ct_5122->AddEntry(kCT5122_CH1_Output_Control, 0x7000, 0x03, 1);
    

    PDOEntriesList* txpdo_ct_623f = new PDOEntriesList();
	txpdo_ct_623f->AddEntry(kCT632F_DI0, 0x6001, 0x01, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI1, 0x6001, 0x02, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI2, 0x6001, 0x03, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI3, 0x6001, 0x04, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI4, 0x6001, 0x05, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI5, 0x6001, 0x06, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI6, 0x6001, 0x07, 1);
	txpdo_ct_623f->AddEntry(kCT632F_DI7, 0x6001, 0x08, 1);

    PDOEntriesList* rxpdo_ct_623f = new PDOEntriesList();
    rxpdo_ct_623f->AddEntry(kCT632F_DO0, 0x7001, 0x01, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO1, 0x7001, 0x02, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO2, 0x7001, 0x03, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO3, 0x7001, 0x04, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO4, 0x7001, 0x05, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO5, 0x7001, 0x06, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO6, 0x7001, 0x07, 1);
	rxpdo_ct_623f->AddEntry(kCT632F_DO7, 0x7001, 0x08, 1);

    /* Внимательно с нумерацией PDO! */
    sync = new AdvancedSyncInfo();
    sync->AddTxPDO(0x1A00, txpdo_ct_5122);
    sync->AddRxPDO(0x1600, rxpdo_ct_5122);
    sync->AddTxPDO(0x1A01, txpdo_ct_623f);
    sync->AddRxPDO(0x1601, rxpdo_ct_623f);
    sync->Create();

    ecat_io_module->RegisterSync(sync);
    ecat_io_module->RegisterParameterSDO(nullptr);
    ecat_io_module->RegisterTelemetrySDO(nullptr);
    
    return ecat_io_module;
}