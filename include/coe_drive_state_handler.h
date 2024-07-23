#ifndef COE_DRIVE_STATE_HANDLER_H
#define COE_DRIVE_STATE_HANDLER_H

#include <stdint.h>

namespace coe_drive_state_handler
{
	enum ModeOfOperation
	{
		kModeUndefined					 = 0x00,
		kModeProfilePosition			 = 0x01,
		kModeProfileVelocity			 = 0x03,
		kModeProfileTorque				 = 0x04,
		kModeHoming						 = 0x06,
		kModeCyclicSynchronousPosition	 = 0x08,
		kModeCyclicSynchronousVelocity	 = 0x09,
		kModeCyclicSynchronousTorque	 = 0x0A
	};

	enum PowerDriveSystemState
	{
		kStateUndefined			 	= 0,	
		kStateNotReadyToSwitchOn 	= 1,
		kStateSwitchOnDisabled 		= 2,
		kStateReadyToSwitchOn 		= 3,
		kStateSwitchedOn 			= 4,
		kStateOperationEnabled 		= 5,
		kStateQuickStopActive 		= 6,
		kStateFaultReactionActive 	= 7,
		kStateFault 				= 8
	};

	enum PowerDriveSystemCommand
	{
		kCommandShutdown		 = 0,
		kCommandSwitchOn		 = 1,
		kCommandEnableOperation	 = 2,
		kCommandDisableVoltage	 = 3,
		kCommandQuickStop		 = 4,
		kCommandDisableOperation = 5,
		kCommandFaultReset		 = 6
	};

	void ApplyPDSCommandToControlword(const PowerDriveSystemCommand command, const int64_t *controlword);
	PowerDriveSystemState GetPDSStateFromStatusword(int64_t* const statusword);
}

#endif