#include "real_gantry.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"
#include "coe_drive_state_handler.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

RealGantry::RealGantry(uint32_t microstep_resolution, float gear_ratio) : Gantry(microstep_resolution, gear_ratio)
{}

bool RealGantry::IsEmulated()
{
    return false;
}

void RealGantry::ModifyTelemetry()
{
	constexpr float kDegreesPerRotation = 360;
	int64_t statusword = this->drive->GetTxPDOEntry(kStatusword)->LoadValue();

	auto telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();

	telemetry->pds_drive_state = coe_drive_state_handler::GetPDSStateFromStatusword(&statusword);
	telemetry->is_drive_enabled = (telemetry->pds_drive_state == coe_drive_state_handler::kStateOperationEnabled);
	telemetry->drive_position_pulse = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
    telemetry->drive_velocity_pulse_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
    telemetry->drive_position_deg = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue() 
		/ props.microstep_resolution / props.gear_ratio * kDegreesPerRotation;
    telemetry->drive_velocity_deg_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue()
		/ props.microstep_resolution / props.gear_ratio * kDegreesPerRotation;

}
