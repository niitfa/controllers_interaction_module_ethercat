#include "kv_filter_drive.h"

KVFilterDrive::~KVFilterDrive()
{
    delete wire_sensor;
}

KVFilterDrive::KVFilterDrive(uint32_t microstep_resolution, float thread_pitch)
{
    this->props.microstep_resolution = microstep_resolution;
    this->props.thread_pitch = thread_pitch;
}

void KVFilterDrive::Action()
{
    if(this->wire_sensor) wire_sensor->Update();
    SubsystemContentCreator<KVFilterDriveContext, KVFilterDriveTask, KVFilterDrive, KVFilterDriveTelemetry>::Action(); 
}

KVFilterDrive::Properties KVFilterDrive::GetProperties()
{
    return this->props;
}

void KVFilterDrive::RegisterWireSensor(WireSensor* sensor)
{
    this->wire_sensor = sensor;
}

void KVFilterDrive::RegisterDrive(EthercatSlave* drive)
{
    this->drive = drive;
}

EthercatSlave* KVFilterDrive::GetDrive()
{
    return this->drive;
}