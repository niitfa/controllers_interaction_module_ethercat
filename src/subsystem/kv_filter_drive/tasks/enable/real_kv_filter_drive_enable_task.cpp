#include "kv_filter_drive_enable_task.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

using namespace coe_drive_state_handler;
using namespace coe_object_names;

void RealKVFilterDriveEnableTask::StateRun()
{
	auto drive = GetContext()->GetSubsystem()->GetDrive();
	int64_t statusword = drive->GetTxPDOEntry(kStatusword)->LoadValue();
	int64_t controlword = drive->GetRxPDOEntry(kControlword)->LoadValue();

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

	drive->GetRxPDOEntry(kControlword)->StoreValue(controlword);

	if(psd_state == kStateOperationEnabled)
	{
		GetContext()->TransitToNext();
	}
}