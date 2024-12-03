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

//by MPEI
int cnt = 0;
double T = 0.2;
double actVeloutPrev = 0; 
double actVelout = 0;
bool constSpeedDO_1 = false;
bool impulsePosDO_2 = false;
uint32_t DOs = 0;
int64_t delta = 242;
int impulsState = 0;
int32_t posCNT = 0;
int32_t posCNTPrev = 0;
///////////////////////////

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

	//by MPEI
	int64_t targetVel = context->GetSubsystem()->GetEthercatConfig()->GetSlave(kGantryDriveNameMKLKT)->GetRxPDOEntry(kProfileVelocity)->LoadValue();
	int64_t currentVel = this->drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
	int64_t currentPos = this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();	

	actVeloutPrev = actVelout;
	actVelout = (1.0 - 0.001 / T) * actVeloutPrev +  (0.001 / T) * currentVel;


	if (targetVel != 0) {
		if (targetVel-970 <= abs(actVelout) && targetVel+970 >= abs(actVelout)) {
		// if (targetVel*0.5 <= abs(actVelout) && targetVel*1.5 >= abs(actVelout)) {	
			if (cnt >= 10) {
				constSpeedDO_1 = true;				
			} else {
				constSpeedDO_1 = false;				
				cnt++;
			}
		} else {
			cnt = 0;
			constSpeedDO_1 = false; 			
		}
	} else {
		constSpeedDO_1 = false; 		
	}	

	posCNTPrev = posCNT;
	posCNT = 360.0 * 20 / 1745730 * currentPos;
	if (posCNT != posCNTPrev) {
		impulsePosDO_2 = true;
	}
	else {
		impulsePosDO_2 = false;
	}
	
	DOs = (constSpeedDO_1 << 16) + (impulsePosDO_2 << 17);
	context->GetSubsystem()->GetEthercatConfig()->GetSlave(kGantryDriveNameMKLKT)->GetRxPDOEntry(kDigitalOutputs)->StoreValue(DOs);
	///////////////////////////////////////////////	
}
