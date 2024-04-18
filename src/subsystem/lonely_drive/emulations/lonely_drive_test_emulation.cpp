#include "lonely_drive_test_emulation.h"

LonelyDriveTestEmulation::LonelyDriveTestEmulation()
{
	this->cnt = 0;
}

void LonelyDriveTestEmulation::RunEvent()
{
	//auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
	//telemetry->drive_position_count = cnt--;
	std::cout << "Emulated event " << ++cnt << "...\n";
	if(cnt == 100)
	{
		this->EndThisEvent();
	}
}