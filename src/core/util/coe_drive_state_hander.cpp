#include "coe_drive_state_handler.h"
#include "word_bit.h"
#include <iostream>

namespace coe_drive_state_handler
{
	void ApplyPDSCommandToControlword(const PowerDriveSystemCommand command, const int64_t* controlword)
	{
		switch(command)
		{
			case kCommandShutdown:
			WordBit::Write((int64_t*)controlword, 0, 0);
			WordBit::Write((int64_t*)controlword, 1, 1);
			WordBit::Write((int64_t*)controlword, 2, 1);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandSwitchOn:
			WordBit::Write((int64_t*)controlword, 0, 1);
			WordBit::Write((int64_t*)controlword, 1, 1);
			WordBit::Write((int64_t*)controlword, 2, 1);
			WordBit::Write((int64_t*)controlword, 3, 0);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandEnableOperation:
			WordBit::Write((int64_t*)controlword, 0, 1);
			WordBit::Write((int64_t*)controlword, 1, 1);
			WordBit::Write((int64_t*)controlword, 2, 1);
			WordBit::Write((int64_t*)controlword, 3, 1);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandDisableVoltage:
			WordBit::Write((int64_t*)controlword, 1, 0);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandQuickStop:
			WordBit::Write((int64_t*)controlword, 1, 1);
			WordBit::Write((int64_t*)controlword, 2, 0);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandDisableOperation:
			WordBit::Write((int64_t*)controlword, 0, 1);
			WordBit::Write((int64_t*)controlword, 1, 1);
			WordBit::Write((int64_t*)controlword, 2, 1);
			WordBit::Write((int64_t*)controlword, 3, 0);
			WordBit::Write((int64_t*)controlword, 7, 0);
			break;
			case kCommandFaultReset:
			WordBit::Write((int64_t*)controlword, 7, 1);
			break;
		}
	}

	PowerDriveSystemState GetPDSStateFromStatusword(int64_t* const statusword)
	{
		const uint8_t kNumberOfBits = 7;
		uint8_t bits[kNumberOfBits];

		for (int i = 0; i < kNumberOfBits; ++i)
		{
			bits[i] = WordBit::Read((int64_t*)statusword, i);
		}

		if(!bits[6] && !bits[3] && !bits[2] && !bits[1] && !bits[0])
			return kStateNotReadyToSwitchOn;
		if(bits[6] && !bits[3] && !bits[2] && !bits[1] && !bits[0])
			return kStateSwitchOnDisabled;
		if(!bits[6] && bits[5] && !bits[3] && !bits[2] && !bits[1] && bits[0])
			return kStateReadyToSwitchOn;
		if(!bits[6] && bits[5] && !bits[3] && !bits[2] && bits[1] && bits[0])
			return kStateSwitchedOn;
		if(!bits[6] && bits[5] && !bits[3] && bits[2] && bits[1] && bits[0])
			return kStateOperationEnabled;
		if(!bits[6] && !bits[5] && !bits[3] && bits[2] && bits[1] && bits[0])
			return kStateQuickStopActive;
		if(!bits[6] && bits[3] && bits[2] && bits[1] && bits[0])
			return kStateFaultReactionActive;
		if(!bits[6] && bits[3] && !bits[2] && !bits[1] && !bits[0])
			return kStateFault;
		return kStateUndefined;
	}
}

