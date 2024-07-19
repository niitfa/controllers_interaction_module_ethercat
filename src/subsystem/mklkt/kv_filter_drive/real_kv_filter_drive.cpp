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
	int64_t statusword = this->drive->GetTxPDOEntry(kStatusword)->LoadValue();

	telemetry->pds_drive_state = coe_drive_state_handler::GetPDSStateFromStatusword(&statusword);
	telemetry->is_drive_enabled = (telemetry->pds_drive_state == coe_drive_state_handler::kStateOperationEnabled);

    telemetry->drive_position_pulse = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
    telemetry->drive_velocity_pulse_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
    telemetry->drive_position_mm = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    telemetry->drive_velocity_mm_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue() * props.thread_pitch / props.microstep_resolution;
}