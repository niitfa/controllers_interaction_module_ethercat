#include "real_kv_filter_drive.h"

RealKVFilterDrive::~RealKVFilterDrive()
{
    delete wire_sensor;
}

bool RealKVFilterDrive::IsEmulated()
{
    return false;
}

void RealKVFilterDrive::RegisterWireSensor(WireSensor* sensor)
{
    this->wire_sensor = sensor;
}

void RealKVFilterDrive::RegisterDrive(EthercatSlave* drive)
{
    this->drive = drive;
}

void RealKVFilterDrive::Action()
{
    if(this->wire_sensor) wire_sensor->Update();
    //std::cout << "RealKVFilterDrive::Action(): Wire sensor pos: " << wire_sensor->GetVelocityCountsPerSec() << std::endl;

    KVFilterDrive::Action();
}

void RealKVFilterDrive::UpdateSubsystemTelemetry()
{

}

void RealKVFilterDrive::ModifyTelemetry()
{

}