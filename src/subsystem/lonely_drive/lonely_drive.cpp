#include "lonely_drive.h"
#include "coe_drive_state_handler.h"

using namespace coe_drive_state_handler;

void LonelyDrive::RegisterDrive(EthercatSlave* drive)
{
	this->drive = drive;
}

EthercatSlave* LonelyDrive::GetDrive()
{
	return this->drive;
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

void EmulatedLonelyDrive::ModifyTelemetry()
{}
