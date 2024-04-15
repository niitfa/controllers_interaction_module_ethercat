#include "lonely_drive_enable_task.h"
#include "coe_drive_state_handler.h"

void RealLonelyDriveEnableTask::StateRun()
{
	auto drive = GetContext()->GetSubsystem()->GetDrive();
	int64_t statusword = drive->GetTxPDOEntry("Statusword")->LoadValue();
	int64_t controlword = drive->GetRxPDOEntry("Controlword")->LoadValue();

	PowerDriveSystemState psd_state = GetPDSStateFromStatusword(&statusword);
	switch(psd_state)
	{
		case kStateSwitchOnDisabled:
		ApplyPDSCommandToControlword(kCommandShutdown, &controlword);
		break;
		case kStateReadyToSwitchOn:
		ApplyPDSCommandToControlword(kCommandSwitchOn, &controlword);
		break;
		case kStateSwitchedOn:
		ApplyPDSCommandToControlword(kCommandEnableOperation, &controlword);	
		break;
		case kStateQuickStopActive:
		ApplyPDSCommandToControlword(kCommandDisableVoltage, &controlword);	
		break;
		case kStateFault:
		ApplyPDSCommandToControlword(kCommandFaultReset, &controlword);	
		break;	
	}

	drive->GetRxPDOEntry("Controlword")->StoreValue(controlword);

	if(psd_state == kStateOperationEnabled)
	{
		LonelyDriveTaskState::GetContext()->TransitToNext();
	}
}

void EmulatedLonelyDriveEnableTask::StateRun()
{

}