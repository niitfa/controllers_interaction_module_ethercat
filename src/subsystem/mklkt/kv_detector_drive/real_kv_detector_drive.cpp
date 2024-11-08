#include "real_kv_detector_drive.h"
#include "coe_object_names.h"
#include "ethercat_slave_names.h"
#include "word_bit.h"

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
    int64_t statusword = this->drive->GetTxPDOEntry(kStatusword)->LoadValue();

    telemetry->pds_drive_state = coe_drive_state_handler::GetPDSStateFromStatusword(&statusword);
	telemetry->is_drive_enabled = (telemetry->pds_drive_state == coe_drive_state_handler::kStateOperationEnabled);

    telemetry->drive_position_pulse = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
    telemetry->drive_velocity_pulse_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
    telemetry->drive_position_mm = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue() * props.thread_pitch / props.microstep_resolution;
    telemetry->drive_velocity_mm_per_sec = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue() * props.thread_pitch / props.microstep_resolution;

    // limit switches
	int32_t digital_inputs = this->drive->GetTxPDOEntry(kDigitalInputs)->LoadValue();
	int limit_switch_pos_homing_bit = 19;
	telemetry->limit_switch_homing_positive = WordBit::Read((int64_t*)&digital_inputs, limit_switch_pos_homing_bit);
	int limit_switch_neg_homing_bit = 18;
    telemetry->limit_switch_homing_negative = WordBit::Read((int64_t*)&digital_inputs, limit_switch_neg_homing_bit);
	int limit_switch_pos_user_bit = 17;
    telemetry->limit_switch_user_positive = WordBit::Read((int64_t*)&digital_inputs, limit_switch_pos_user_bit);
	int limit_switch_neg_user_bit = 16;
    telemetry->limit_switch_user_negative = WordBit::Read((int64_t*)&digital_inputs, limit_switch_neg_user_bit);
}