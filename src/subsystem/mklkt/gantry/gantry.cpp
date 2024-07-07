#include "gantry.h"

Gantry::Gantry(uint32_t microstep_resolution, float gear_ratio)
{
    this->props.microstep_resolution = microstep_resolution;
    this->props.gear_ratio = gear_ratio;
}

Gantry::Properties Gantry::GetProperties()
{
    return this->props;
}

void Gantry::RegisterDrive(EthercatSlave* drive)
{
    this->drive = drive;
}

EthercatSlave* Gantry::GetDrive()
{
    return this->drive;
}