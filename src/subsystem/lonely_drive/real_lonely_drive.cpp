#include "real_lonely_drive.h"

using namespace coe_drive_state_handler;

bool RealLonelyDrive::IsEmulated()
{
    return false;
}

void RealLonelyDrive::ModifyTelemetry()
{
	if (this->drive)
	{
		auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
		auto statusword = this->drive->GetRxPDOEntry("Statusword")->LoadValue();
		
		master_telemetry->pds_state = GetPDSStateFromStatusword(&statusword);
		master_telemetry->drive_position_count = this->drive->GetRxPDOEntry("Actual position")->LoadValue();
		master_telemetry->drive_velocity_count_per_sec 	= this->drive->GetTelemetrySDOEntry("Actual velocity")->LoadValue();
	}
}