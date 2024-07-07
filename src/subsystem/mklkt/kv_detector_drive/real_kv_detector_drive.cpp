#include "real_kv_detector_drive.h"
#include "coe_object_names.h"
#include "ethercat_slave_names.h"

using namespace coe_object_names;

RealKVDetectorDrive::RealKVDetectorDrive(uint32_t microstep_resolution, float thread_pitch) : KVDetectorDrive(microstep_resolution, thread_pitch)
{}

bool RealKVDetectorDrive::IsEmulated()
{
    return false;
}

void RealKVDetectorDrive::ModifyTelemetry()
{
    auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
    telemetry->drive_position_pulse = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
    telemetry->drive_velocity_pulse_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
    //telemetry->wire_sensor_position_pulse = this->wire_sensor->GetPositionCounts();
    //telemetry->wire_sensor_position_mm = this->wire_sensor->GetPositionMillimeters();

    telemetry->drive_position_mm = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    telemetry->drive_velocity_mm_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    //telemetry->wire_sensor_velocity_pulse_per_sec = this->wire_sensor->GetVelocityCountsPerSec();
    //telemetry->wire_sensor_velocity_mm_per_sec = this->wire_sensor->GetVelociyMillimetersPerSec();

    /*auto sync0_ct = this->context->GetSubsystem()->GetEthercatConfig()->
        GetSlave(ethercat_slave_names::kIOModuleName)->GetTelemetrySDOEntry("Sync0 cycle time")->LoadValue();
    std::cout << "RealKVDetectorDrive::ModifyTelemetry(): sync0_ct = " << sync0_ct << std::endl; */

}