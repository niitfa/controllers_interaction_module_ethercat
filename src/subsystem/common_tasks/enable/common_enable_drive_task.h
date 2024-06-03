#ifndef COMMON_ENABLE_DRIVE_TASK_H
#define COMMON_ENABLE_DRIVE_TASK_H

#include "ethercat_slave.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

template<class TContext>
class CommonEnableDriveTask
{
public:
    void RunTask(TContext* context);
};

template<class TContext>
void CommonEnableDriveTask<TContext>::RunTask(TContext* context)
{
    EthercatSlave* drive = context->GetSubsystem()->GetDrive();
 	int64_t statusword = drive->GetTxPDOEntry(coe_object_names::kStatusword)->LoadValue();
	int64_t controlword = drive->GetRxPDOEntry(coe_object_names::kControlword)->LoadValue();

	coe_drive_state_handler::PowerDriveSystemState psd_state = coe_drive_state_handler::GetPDSStateFromStatusword(&statusword);
	switch(psd_state)
	{
		case coe_drive_state_handler::kStateSwitchOnDisabled:
		coe_drive_state_handler::ApplyPDSCommandToControlword(coe_drive_state_handler::kCommandShutdown, &controlword);
		break;
		case coe_drive_state_handler::kStateReadyToSwitchOn:
		coe_drive_state_handler::ApplyPDSCommandToControlword(coe_drive_state_handler::kCommandSwitchOn, &controlword);
		break;
		case coe_drive_state_handler::kStateSwitchedOn:
		coe_drive_state_handler::ApplyPDSCommandToControlword(coe_drive_state_handler::kCommandEnableOperation, &controlword);	
		break;
		case coe_drive_state_handler::kStateQuickStopActive:
		coe_drive_state_handler::ApplyPDSCommandToControlword(coe_drive_state_handler::kCommandDisableVoltage, &controlword);	
		break;
		case coe_drive_state_handler::kStateFault:
		coe_drive_state_handler::ApplyPDSCommandToControlword(coe_drive_state_handler::kCommandFaultReset, &controlword);	
		break;	
	}

	drive->GetRxPDOEntry(coe_object_names::kControlword)->StoreValue(controlword);

	if(psd_state == coe_drive_state_handler::kStateOperationEnabled)
	{
		context->TransitToNext();
	}   
}



#endif