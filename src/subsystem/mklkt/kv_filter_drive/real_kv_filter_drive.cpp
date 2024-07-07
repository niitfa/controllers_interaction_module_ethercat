#include "real_kv_filter_drive.h"
#include "coe_object_names.h"
#include "coe_drive_state_handler.h"

using namespace coe_object_names;

RealKVFilterDrive::RealKVFilterDrive(uint32_t microstep_resolution, float thread_pitch) : KVFilterDrive(microstep_resolution, thread_pitch)
{}

bool RealKVFilterDrive::IsEmulated()
{
    return false;
}

void RealKVFilterDrive::ModifyTelemetry()
{
    auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
    telemetry->drive_position_pulse = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
    telemetry->drive_velocity_pulse_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
    //telemetry->wire_sensor_position_pulse = this->wire_sensor->GetPositionCounts(); /* No wire sensor */
    //telemetry->wire_sensor_position_mm = this->wire_sensor->GetPositionMillimeters();

    telemetry->drive_position_mm = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    telemetry->drive_velocity_mm_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    //telemetry->wire_sensor_velocity_pulse_per_sec = this->wire_sensor->GetVelocityCountsPerSec();
    //telemetry->wire_sensor_velocity_mm_per_sec = this->wire_sensor->GetVelociyMillimetersPerSec();
}