#ifndef COE_DRIVE_STATE_HANDLER_H
#define COE_DRIVE_STATE_HANDLER_H

#include <stdint.h>

namespace coe_drive_state_handler
{
	enum ModeOfOperation
	{
		kModeUndefined = 0x00,
		kModeProfilePosition = 0x01,
		kModeProfileVelocity = 0x03,
		kModeProfileTorque = 0x04,
		kModeHoming = 0x06,
		kModeCyclicSynchronousPosition = 0x08,
		kModeCyclicSynchronousVelocity = 0x09,
		kModeCyclicSynchronousTorque = 0x0A
	};

	enum PowerDriveSystemState
	{
		kStateUndefined,	
		kStateNotReadyToSwitchOn,
		kStateSwitchOnDisabled,
		kStateReadyToSwitchOn,
		kStateSwitchedOn,
		kStateOperationEnabled,
		kStateQuickStopActive,
		kStateFaultReactionActive,
		kStateFault
	};

	enum PowerDriveSystemCommand
	{
		kCommandShutdown,
		kCommandSwitchOn,
		kCommandEnableOperation,
		kCommandDisableVoltage,
		kCommandQuickStop,
		kCommandDisableOperation,
		kCommandFaultReset
	};

	void ApplyPDSCommandToControlword(const PowerDriveSystemCommand command, const int64_t *controlword);
	PowerDriveSystemState GetPDSStateFromStatusword(const int64_t* const statusword);
}

#endif