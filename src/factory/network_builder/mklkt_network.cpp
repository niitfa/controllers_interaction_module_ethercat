#include "mklkt_network.h"
#include "simple_timer.h"

/* Builders */
#include "io_module_mklkt_builder.h"
#include "gantry_drive_mklkt_builder.h"
#include "kv_filter_drive_mklkt_builder.h"
#include "kv_detector_drive_mklkt_builder.h"

/* Subsystems */
#include "emulated_gantry.h"
#include "real_gantry.h"
#include "emulated_kv_filter_drive.h"
#include "real_kv_filter_drive.h"
#include "emulated_kv_detector_drive.h"
#include "real_kv_detector_drive.h"

MKLKTNetwork::~MKLKTNetwork()
{
    delete thread;
}

void MKLKTNetwork::Build(uint16_t master_index)
{
    delete thread;

    /* Ethercat */
    uint32_t frequency_hz = 1000;

    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);

    EthercatSlave* io_module_slave = (new IOModuleMKLKTBuilder)->Build(0, 1);
    EthercatSlave* gantry_slave = (new GantryDriveMKLKTBuilder)->Build(0, 0);
    EthercatSlave* kv_filter_slave = (new KVFilterDriveMKLKTBuilder)->Build(0, 2);
    EthercatSlave* kv_detector_slave = (new KVDetectorDriveMKLKTBuilder)->Build(0, 3);

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    //ethercat_slaves->RegisterSlave(io_module_slave);
    ethercat_slaves->RegisterSlave(gantry_slave);
    //ethercat_slaves->RegisterSlave(kv_filter_slave);
    //ethercat_slaves->RegisterSlave(kv_detector_slave);

    EthercatTimer* timer = new SimpleTimer();
    timer->SetFrequency(frequency_hz);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
    ethercat_config->RegisterSlavesContainer(ethercat_slaves);
    ethercat_config->RegisterTimer(timer);

    /* Gantry */
    Gantry* gantry;
    if(is_gantry_emulated)
    {
        gantry = new EmulatedGantry(65536, 1745730./65536);
    }
    else
    {
        gantry = new RealGantry(65536, 1745730./65536);
        gantry->RegisterDrive(gantry_slave);
    }

    /* kV filter drive */
    KVFilterDrive* kv_filter_drive;
    if(is_kv_filter_emulated)
    {
        kv_filter_drive = new EmulatedKVFilterDrive(10000, 4);
    }
    else
    {
        kv_filter_drive = new RealKVFilterDrive(10000, 4);
        kv_filter_drive->RegisterDrive(kv_filter_slave);
    }

    KVDetectorDrive* kv_detector_drive;
    if(is_kv_detector_emulated)
    {
        kv_detector_drive = new EmulatedKVDetectorDrive(10000, 4);
    }
    else
    {
        kv_detector_drive = new RealKVDetectorDrive(10000, 4);
        kv_detector_drive->RegisterDrive(kv_detector_slave);
    }


    this->device = new MKLKTModel();
    device->RegisterGantry(gantry);
    device->RegisterKVFilterDrive(kv_filter_drive);
    device->RegisterKVDetectorDrive(kv_detector_drive);
    device->RegisterEthercatConfig(ethercat_config);

    this->thread = new EthercatThreadManager();
    thread->RegisterDevice(device);
}

void MKLKTNetwork::StartThread()
{
    if(thread)
    {
        started = true;
        thread->StartThread();
    }
}

void MKLKTNetwork::StopThread()
{
    if(thread)
    {
        thread->StopThread();
        started = false;
    }
}

void MKLKTNetwork::SetGantryEmulationStatus(bool status)
{
    if(!started)
    {
        is_gantry_emulated = status;
    }
}

void MKLKTNetwork::SetKVDetectorDriveEmulatonStatus(bool status)
{
    if(!started)
    {
        is_kv_detector_emulated = status;
    }
}

void MKLKTNetwork::SetKVFilterDriveEmulatonStatus(bool status)
{
    if(!started)
    {
        is_kv_filter_emulated = status;
    }
}

MKLKTModel* MKLKTNetwork::GetDevice()
{
    return device;
}


