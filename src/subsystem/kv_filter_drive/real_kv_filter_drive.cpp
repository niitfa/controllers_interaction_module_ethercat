#include "real_kv_filter_drive.h"
#include "coe_object_names.h"

RealKVFilterDrive::RealKVFilterDrive(uint32_t microstep_resolution, float thread_pitch) : KVFilterDrive(microstep_resolution, thread_pitch)
{}

bool RealKVFilterDrive::IsEmulated()
{
    return false;
}

void RealKVFilterDrive::ModifyTelemetry()
{
    auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
    telemetry->wire_sensor_velocity_mm = this->wire_sensor->GetVelociyMillimetersPerSec();
    //std::cout << "wire: " << telemetry->wire_sensor_velocity_mm << std::endl;
}