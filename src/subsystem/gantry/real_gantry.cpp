#include "real_gantry.h"

bool RealGantry::IsEmulated()
{
    return false;
}

void RealGantry::ModifyTelemetry()
{
	auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
	auto gantry_drive = this->GetEthercatConfig()->GetSlaves()->GetSlave("Gantry drive");

	master_telemetry->gantry_position_count 		= gantry_drive->GetRxPDOEntry("Actual position")->LoadValue();
	master_telemetry->gantry_velocity_count_per_sec = gantry_drive->GetTelemetrySDOEntry("Actual velocity")->LoadValue();	
}
