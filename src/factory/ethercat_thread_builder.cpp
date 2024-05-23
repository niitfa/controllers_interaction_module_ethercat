#include "ethercat_thread_builder.h"
#include "ethercat_thread_manager.h"
#include "ethercat_slave_builder.h"
#include "ethercat_slaves_container.h"
#include "dc_master_to_reference_timer.h"
#include "simple_timer.h"
#include "io_module_cn8033.h"
#include "real_kv_filter_drive.h"
#include "coe_object_names.h"

EthercatThreadBuilder::IOModuleThreadContent EthercatThreadBuilder::BuildThread_IOModule(int master_index)
{
    uint32_t frequency_hz = 1000;
    uint32_t dc_shift_us = 500;


    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    EthercatSlave* io_module_cn_8033 = EthercatSlaveBuilder::BuildIOModule(0, 0);
    ethercat_slaves->RegisterSlave(io_module_cn_8033);

	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	timer->SetReferenceSlaveClock(io_module_cn_8033);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

    IOModuleCN8033* io_module = new IOModuleCN8033();
    io_module->RegisterIOModule(io_module_cn_8033);
    
    UnspecifiedDevice* device = new UnspecifiedDevice();
    device->RegisterSubsystem(io_module);
    device->RegisterEthercatConfig(ethercat_config);

    EthercatThreadManager* thread = new EthercatThreadManager(); 
    thread->RegisterDevice(device);
    thread->SetCPUs({13});   


    IOModuleThreadContent thread_content;
    thread_content.thread = thread;   
    thread_content.device = device;
    thread_content.io_module = io_module;

    return thread_content;

}

EthercatThreadBuilder::DriveThreadContent EthercatThreadBuilder::BuildThread_Drive(int master_index)
{
    uint32_t frequency_hz = 1000;
    uint32_t dc_shift_us = 500;

    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    EthercatSlave* leadshine_drive = EthercatSlaveBuilder::BuildKVFilterDrive(0, 0);
    ethercat_slaves->RegisterSlave(leadshine_drive);

	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	timer->SetReferenceSlaveClock(leadshine_drive);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

    //IOModuleCN8033* io_module = new IOModuleCN8033();
    //io_module->RegisterIOModule(io_module_cn_8033);
    RealLonelyDrive* lonely_drive = new RealLonelyDrive();
    lonely_drive->RegisterDrive(leadshine_drive);
    
    UnspecifiedDevice* device = new UnspecifiedDevice();
    device->RegisterSubsystem(lonely_drive);
    device->RegisterEthercatConfig(ethercat_config);

    EthercatThreadManager* thread = new EthercatThreadManager(); 
    thread->RegisterDevice(device);
    thread->SetCPUs({13});   


    DriveThreadContent thread_content;
    thread_content.thread = thread;   
    thread_content.device = device;
    thread_content.drive = lonely_drive;

    return thread_content;
}

EthercatThreadBuilder::Drive_IOModule_ThreadContent EthercatThreadBuilder::BuildThread_Drive_IOModule(int master_index)
{
    uint32_t frequency_hz = 1000;
    uint32_t dc_shift_us = 500;

    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    EthercatSlave* leadshine_dm3c_ec556_drive = EthercatSlaveBuilder::BuildKVFilterDrive(0, 0);
    leadshine_dm3c_ec556_drive->SetAssignActivate(0x0300); 
    leadshine_dm3c_ec556_drive->WithDistributedClocks();
    EthercatSlave* io_module_cn_8033 = EthercatSlaveBuilder::BuildIOModule(0, 1);
   // io_module_cn_8033->SetAssignActivate(0x0100); 
    //io_module_cn_8033->WithDistributedClocks();

    ethercat_slaves->RegisterSlave(io_module_cn_8033);
    ethercat_slaves->RegisterSlave(leadshine_dm3c_ec556_drive);

	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	timer->SetReferenceSlaveClock(leadshine_dm3c_ec556_drive);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

    WireSensor* sensor = new WireSensor(100);
    sensor->SetFrequency(frequency_hz);
    sensor->SetPowerSupply(24);
    sensor->SetVoltPerCount(10. / 27648);
    sensor->SetOutput(10);
    sensor->SetPositionAddress(
        io_module_cn_8033->GetTxPDOEntry(coe_object_names::kCT3168_AI0)->GetValueAddress()
    );

    RealKVFilterDrive* kV_filter_drive = new RealKVFilterDrive();
    kV_filter_drive->RegisterWireSensor(sensor);
    kV_filter_drive->RegisterDrive(io_module_cn_8033);
    
    UnspecifiedDevice* device = new UnspecifiedDevice();
    device->RegisterSubsystem(kV_filter_drive);
    device->RegisterEthercatConfig(ethercat_config);

    EthercatThreadManager* thread = new EthercatThreadManager(); 
    thread->RegisterDevice(device);
    thread->SetCPUs({13});   


    Drive_IOModule_ThreadContent thread_content;
    thread_content.thread = thread;   
    thread_content.device = device;
    thread_content.kv_drive = kV_filter_drive;

    return thread_content;
}