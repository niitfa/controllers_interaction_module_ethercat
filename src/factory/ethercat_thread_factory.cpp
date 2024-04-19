#include "ethercat_thread_factory.h"
#include "device_model.h"
#include "ethercat_configuration.h"
#include "ethercat_slave.h"
#include "dc_master_to_reference_timer.h"
#include "default_sync_info.h"
#include "sdo_list.h"
#include "ethercat_slave.h"

#include "coe_object_names.h"
#include "ethercat_slave_names.h"

using namespace coe_object_names;
using namespace ethercat_slave_names;

void ConfigureNetwork_0(EthercatThreadManager* thread, UnspecifiedDevice* device,  LonelyDrive* mech_subsystem)
{
	uint32_t frequency_hz = 1000;
	uint32_t dc_shift_us = 500;
	uint32_t sdo_timeout_ms = 500;

	/* Building ethercat master */
	EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(0);

	/* Building slaves */
	EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();

	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	DefaultSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	EthercatSlave* hiwin_ed1f_coe_drive = new EthercatSlave();
	hiwin_ed1f_coe_drive->SetSlaveInfo(kGantryDrive, 0, 0, 0xAAAA, 0x0005);

	rxpdo = new PDOEntriesList();
	rxpdo->AddEntry(kControlword, 0x6040, 0x00, 16);
	rxpdo->AddEntry(kModeOfOperation, 0x6060, 0x00, 8);
	rxpdo->AddEntry(kTargetPosition, 0x607A, 0x00, 32);

	txpdo = new PDOEntriesList();
	txpdo->AddEntry(kStatusword, 0x6041, 0x00, 16);
	txpdo->AddEntry(kModeOfOperationOut, 0x6061, 0x00, 8);
	txpdo->AddEntry(kActualPosition, 0x6064, 0x00, 32);

	sync = new DefaultSyncInfo();
	sync->AddRxPDO(0x1600, rxpdo);	
	sync->AddTxPDO(0x1A00, txpdo);
	sync->Create();

	sdo_parameters = new SDOList();
	sdo_parameters->AddObject(kMaxProfileVelocity, 0x607F, 0x00, 32, 500000);
	sdo_parameters->AddObject(kProfileVelocity, 0x6081, 0x00, 32, 500000);
	sdo_parameters->AddObject(kProfileAcceleration, 0x6083, 0x00, 32, 1500000);
	sdo_parameters->AddObject(kProfileDeceleration, 0x6084, 0x00, 32, 1500000);		
	sdo_parameters->SetTimeout(sdo_timeout_ms);
	sdo_telemetry = new SDOList();
	sdo_telemetry->AddObject(kActualVelocity, 0x606C, 0x00, 32);
	sdo_telemetry->SetTimeout(sdo_timeout_ms);

	hiwin_ed1f_coe_drive->RegisterSync(sync);
	hiwin_ed1f_coe_drive->RegisterParameterSDO(sdo_parameters);
	hiwin_ed1f_coe_drive->RegisterTelemetrySDO(sdo_telemetry);	
	hiwin_ed1f_coe_drive->SetAssignActivate(0x0300);
	ethercat_slaves->RegisterSlave(hiwin_ed1f_coe_drive);

	/* Building timer */
	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	timer->SetReferenceSlaveClock(hiwin_ed1f_coe_drive);

	/* Aggregation ethercat units in configuration object */
	EthercatConfiguration* ethercat_config = new EthercatConfiguration();
	ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

	/* Building subsystems */
	mech_subsystem->RegisterDrive(hiwin_ed1f_coe_drive);
	device->RegisterSubsystem(mech_subsystem);
	/* Final */
	device->RegisterEthercatConfig(ethercat_config);
	/* Building device */
	thread->RegisterDevice(device);
}

void ConfigureNetwork_1(EthercatThreadManager* thread, UnspecifiedDevice* device,  LonelyDrive* mech_subsystem)
{
	uint32_t frequency_hz = 1000;
	uint32_t dc_shift_us = 500;
	uint32_t sdo_timeout_ms = 500;

	/* Building ethercat master */
	EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(1);

	/* Building slaves */
	EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();

	PDOEntriesList* rxpdo;
	PDOEntriesList* txpdo;
	DefaultSyncInfo* sync;
	SDOList* sdo_parameters;
	SDOList* sdo_telemetry;

	EthercatSlave* leadshine_em3e_556_coe_drive = new EthercatSlave();
	leadshine_em3e_556_coe_drive->SetSlaveInfo(kGantryDrive, 0, 0, 0x00004321, 0x00008600);

	rxpdo = new PDOEntriesList();
	rxpdo->AddEntry(kControlword, 0x6040, 0x00, 16);
	rxpdo->AddEntry(kModeOfOperation, 0x6060, 0x00, 8);
	rxpdo->AddEntry(kTargetPosition, 0x607A, 0x00, 32);
	txpdo = new PDOEntriesList();
	txpdo->AddEntry(kStatusword, 0x6041, 0x00, 16);
	txpdo->AddEntry(kModeOfOperationOut, 0x6061, 0x00, 8);
	txpdo->AddEntry(kActualPosition, 0x6064, 0x00, 32);
	sync = new DefaultSyncInfo();
	sync->AddRxPDO(0x1600, rxpdo);	
	sync->AddTxPDO(0x1A00, txpdo);
	sync->Create();

	sdo_parameters = new SDOList();
	sdo_parameters->AddObject(kMicrostepResolution, 0x2001, 0x00, 32, 200);	
	sdo_parameters->AddObject(kProfileVelocity, 0x6081, 0x00, 32, 500);
	sdo_parameters->AddObject(kProfileAcceleration, 0x6083, 0x00, 32, 2000);
	sdo_parameters->AddObject(kProfileDeceleration, 0x6084, 0x00, 32, 2000);	

	sdo_parameters->SetTimeout(sdo_timeout_ms);
	sdo_telemetry = new SDOList();
	sdo_telemetry->AddObject(kActualVelocity, 0x606C, 0x00, 32);
	sdo_telemetry->SetTimeout(sdo_timeout_ms);

	leadshine_em3e_556_coe_drive->RegisterSync(sync);
	leadshine_em3e_556_coe_drive->RegisterParameterSDO(sdo_parameters);
	leadshine_em3e_556_coe_drive->RegisterTelemetrySDO(sdo_telemetry);	
	leadshine_em3e_556_coe_drive->SetAssignActivate(0x0300);
	ethercat_slaves->RegisterSlave(leadshine_em3e_556_coe_drive);

	/* Building timer */
	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	timer->SetReferenceSlaveClock(leadshine_em3e_556_coe_drive);

	/* Aggregation ethercat units in configuration object */
	EthercatConfiguration* ethercat_config = new EthercatConfiguration();
	ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

	/* Building subsystems */
	mech_subsystem->RegisterDrive(leadshine_em3e_556_coe_drive);
	device->RegisterSubsystem(mech_subsystem);
	/* Final */
	device->RegisterEthercatConfig(ethercat_config);
	/* Building device */
	thread->RegisterDevice(device);
}