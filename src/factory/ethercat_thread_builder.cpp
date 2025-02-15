#include "ethercat_thread_builder.h"
#include "ethercat_thread_manager.h"
#include "ethercat_slave_builder.h"
#include "ethercat_slaves_container.h"
#include "dc_master_to_reference_timer.h"
#include "dc_reference_to_master_timer.h"
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

    WireSensor* sensor = new WireSensor(50);
    sensor->SetFrequency(frequency_hz);
    sensor->SetPowerSupply(5);
    sensor->SetVoltPerCount(10. / 27648);
    sensor->SetOutput(10.1);
    sensor->SetPositionAddress(
        io_module_cn_8033->GetTxPDOEntry(coe_object_names::kCT3168_AI0)->GetValueAddress()
    );
    
    /* Drive properties */
    uint32_t microstep_resolution;
    auto microstep_resolution_object = leadshine_dm3c_ec556_drive->GetParameterSDOEntry(coe_object_names::kMicrostepResolution);
    if(microstep_resolution_object)
    {
        microstep_resolution = microstep_resolution_object->LoadValue();
    }
    else
    {
        microstep_resolution = 1000;
    }
    float thread_pitch = 2;

    RealKVFilterDrive* kV_filter_drive = new RealKVFilterDrive(microstep_resolution, thread_pitch);
    kV_filter_drive->RegisterWireSensor(sensor);
    kV_filter_drive->RegisterDrive(leadshine_dm3c_ec556_drive);
    
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

EthercatThreadBuilder::KVFiltDrive_IOModule_KVDetDrive_ThreadContent EthercatThreadBuilder::BuildThread_KVFiltDrive_IOModule_KVDetDrive(int master_index)
{
    uint32_t frequency_hz = 1000;
    uint32_t dc_shift_us = 500;

    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);


    EthercatSlave* kv_filter_drive = EthercatSlaveBuilder::BuildKVFilterDrive(0, 1);
    kv_filter_drive->SetAssignActivate(0x0300); 
    kv_filter_drive->WithDistributedClocks();
    EthercatSlave* io_module_cn_8033 = EthercatSlaveBuilder::BuildIOModule(0, 2);
    //io_module_cn_8033->SetAssignActivate(0x0100); 
    //io_module_cn_8033->WithDistributedClocks(); 
    EthercatSlave* kv_detector_drive = EthercatSlaveBuilder::BuildKVDetectorDrive(0, 0);
    kv_detector_drive->SetAssignActivate(0x0300); 
    kv_detector_drive->WithDistributedClocks(); 

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    ethercat_slaves->RegisterSlave(kv_filter_drive);
    ethercat_slaves->RegisterSlave(io_module_cn_8033);
    ethercat_slaves->RegisterSlave(kv_detector_drive);

	DCMasterToReferenceTimer* timer = new DCMasterToReferenceTimer();
    //DCReferenceToMasterTimer* timer = new DCReferenceToMasterTimer();
	timer->SetFrequency(frequency_hz);
	timer->SetShiftMicroseconds(dc_shift_us);
	timer->SetMaster(ethercat_master);
	timer->SetSlavesClocks(ethercat_slaves);
	//timer->SetReferenceSlaveClock(kv_detector_drive);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

    WireSensor* kv_filter_sensor = new WireSensor(50);
    kv_filter_sensor->SetFrequency(frequency_hz);
    kv_filter_sensor->SetPowerSupply(5);
    kv_filter_sensor->SetVoltPerCount(10. / 27648);
    kv_filter_sensor->SetOutput(10.1);
    kv_filter_sensor->SetPositionAddress(
        io_module_cn_8033->GetTxPDOEntry(coe_object_names::kCT3168_AI0)->GetValueAddress()
    );

    WireSensor* kv_detector_sensor = new WireSensor(500);
    kv_detector_sensor->SetFrequency(frequency_hz);
    kv_detector_sensor->SetPowerSupply(24);
    kv_detector_sensor->SetVoltPerCount(10. / 27648);
    kv_detector_sensor->SetOutput(3.5);
    kv_detector_sensor->SetPositionAddress(
        io_module_cn_8033->GetTxPDOEntry(coe_object_names::kCT3168_AI1)->GetValueAddress()
    );
    
    /* kV filter properties */
    uint32_t microstep_resolution;
    float thread_pitch;
    auto microstep_resolution_object = kv_filter_drive->GetParameterSDOEntry(coe_object_names::kMicrostepResolution);
    if(microstep_resolution_object)
    {
        microstep_resolution = microstep_resolution_object->LoadValue();
    }
    else
    {
        microstep_resolution = 1000;
    }
    thread_pitch = 2;

    RealKVFilterDrive* kV_filter = new RealKVFilterDrive(microstep_resolution, thread_pitch);
    kV_filter->RegisterWireSensor(kv_filter_sensor);
    kV_filter->RegisterDrive(kv_filter_drive);

    /* kV detector properties */
    microstep_resolution_object = kv_detector_drive->GetParameterSDOEntry(coe_object_names::kMicrostepResolution);
    if(microstep_resolution_object)
    {
        microstep_resolution = microstep_resolution_object->LoadValue();
    }
    else
    {
        microstep_resolution = 1000;
    }
    thread_pitch = 2.5;

    RealKVDetectorDrive* kV_detector = new RealKVDetectorDrive(microstep_resolution, thread_pitch);
    kV_detector->RegisterWireSensor(kv_detector_sensor);
    kV_detector->RegisterDrive(kv_detector_drive);
    
    UnspecifiedDevice* device = new UnspecifiedDevice();
    device->RegisterSubsystem(kV_filter);
    device->RegisterSubsystem(kV_detector);
    device->RegisterEthercatConfig(ethercat_config);

    EthercatThreadManager* thread = new EthercatThreadManager(); 
    thread->RegisterDevice(device);
    thread->SetCPUs({13});   
    
    KVFiltDrive_IOModule_KVDetDrive_ThreadContent thread_content;
    thread_content.thread = thread;
    thread_content.device = device;
    thread_content.kv_filter_drive = kV_filter; 
    thread_content.kv_detector_drive = kV_detector; 

    return thread_content;      
}