#include "gantry_drive_mklkt_builder.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"
#include "advanced_sync_info.h"
#include "sdo_list.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

EthercatSlave* GantryDriveMKLKTBuilder::Build(uint16_t alias, uint16_t position)
{
    int drive_counts_per_round = 65536; // 23-разрядный двигатель
    //int drive_counts_per_round = 10000;
    EthercatSlave* ecat_drive = new EthercatSlave();

    /* Уточнить список после получение инф. о модели драйвера*/
    ecat_drive->SetSlaveInfo(kGantryDriveNameMKLKT, alias, position, 0x0000AAAA, 0x00000005);

    AdvancedSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

    /* Уточнить список после получение инф. о модели драйвера*/
    PDOEntriesList* rxpdo = new PDOEntriesList();
    rxpdo->AddEntry(kControlword, 0x6040, 0x00, 16); // 1
    rxpdo->AddEntry(kModeOfOperation, 0x6060, 0x00, 8); // 2
    rxpdo->AddEntry(kTargetPosition, 0x607A, 0x00, 32); // 3
    rxpdo->AddEntry(kTargetVelocity, 0x60FF, 0x00, 32); // 4
    rxpdo->AddEntry(kProfileVelocity, 0x6081, 0x00, 32); // 5
    rxpdo->AddEntry(kHomingMethod, 0x6098, 0x00, 8);
    //by MPEI
    rxpdo->AddEntry(kDigitalOutputs, 0x60FE, 0x01, 32);
    //

    PDOEntriesList* txpdo = new PDOEntriesList();
    txpdo->AddEntry(kStatusword, 0x6041, 0x00, 16);
    txpdo->AddEntry(kModeOfOperationOut, 0x6061, 0x00, 8);
    txpdo->AddEntry(kActualPosition, 0x6064, 0x00, 32);
    txpdo->AddEntry(kActualVelocity, 0x606C, 0x00, 32);
    txpdo->AddEntry(kDigitalInputs, 0x60FD, 0x00, 32);

    sync = new AdvancedSyncInfo();
    sync->AddRxPDO(0x1600, rxpdo);
    sync->AddTxPDO(0x1A00, txpdo);
    sync->Create();

    sdo_parameters = new SDOList();
    sdo_parameters->AddObject(kProfileAcceleration, 0x6083, 0x00, 32, drive_counts_per_round * 30);
    sdo_parameters->AddObject(kProfileDeceleration, 0x6084, 0x00, 32, drive_counts_per_round * 30);
    sdo_parameters->AddObject(kMaxProfileVelocity, 0x607F, 0x00, 32, drive_counts_per_round * 10);
    sdo_parameters->SetTimeout(500);

    ecat_drive->RegisterSync(sync);
    ecat_drive->RegisterParameterSDO(sdo_parameters);
    ecat_drive->RegisterTelemetrySDO(nullptr);
    
    return ecat_drive;
}