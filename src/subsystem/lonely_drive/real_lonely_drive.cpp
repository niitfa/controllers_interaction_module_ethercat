#include "real_lonely_drive.h"
#include "coe_object_names.h"

using namespace coe_drive_state_handler;
using namespace coe_object_names;

bool RealLonelyDrive::IsEmulated()
{
    return false;
}

void RealLonelyDrive::ModifyTelemetry()
{
	if (this->drive)
	{
		auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
		auto statusword = this->drive->GetRxPDOEntry(kStatusword)->LoadValue();
		
		master_telemetry->pds_state = GetPDSStateFromStatusword(&statusword);
		master_telemetry->drive_position_count = this->drive->GetRxPDOEntry(kActualPosition)->LoadValue();
		master_telemetry->drive_velocity_count_per_sec 	= this->drive->GetTelemetrySDOEntry(kActualVelocity)->LoadValue();
	}
}