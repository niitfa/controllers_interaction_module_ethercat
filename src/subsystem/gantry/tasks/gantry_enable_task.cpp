#include "gantry_enable_task.h"

void RealGantryEnableTask::StateRun()
{
	std::cout << "Real gantry enabling...\n" ; 
	GantryTaskState::GetContext()->TransitToNext();
}

void EmulatedGantryEnableTask::StateRun()
{
	/* auto gantry_drive = GetContext()->GetSubsystem()->GetEthercatConfig()
	->GetSlaves()->GetSlave("Gantry drive");

	auto status = gantry_drive->GetRxPDOEntry("Statusword")->LoadValue();
	auto velocity = gantry_drive->GetTelemetrySDOEntry("Actual velocity")->LoadValue();
	auto position = gantry_drive->GetRxPDOEntry("Actual position")->LoadValue();

	GetMasterTelemetry()->gantry_position_count = position; */

	/*std::cout << "EmulatedGantryEnable:" 
	<< "\tstatus: " << status
	<< "\tvelocity: " << velocity
	<< "\tposition: " << position
	<< std::endl; */
}

