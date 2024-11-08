#include "real_gantry.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"
#include "coe_drive_state_handler.h"
#include "word_bit.h"

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
    telemetry->drive_position_deg = (float)this->drive->GetTxPDOEntry(kActualPosition)->LoadValue()
		 / props.microstep_resolution / props.gear_ratio * kDegreesPerRotation;
    telemetry->drive_velocity_deg_per_sec = (float)this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue()
		/ props.microstep_resolution / props.gear_ratio * kDegreesPerRotation;

	// encoder
    telemetry->drive_encoder_value_counts = this->GetEthercatConfig()->GetSlave(kIOModuleName)->GetTxPDOEntry(kCT5122_CH0_Counter_Val)->LoadValue();
	float encoder_gear_ratio = this->GetProperties().gear_ratio;
    telemetry->drive_encoder_value_deg = (float)telemetry->drive_encoder_value_counts / 4096. / encoder_gear_ratio * kDegreesPerRotation;

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
