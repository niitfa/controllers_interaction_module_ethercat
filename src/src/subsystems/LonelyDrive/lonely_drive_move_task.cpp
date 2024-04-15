#include "lonely_drive_move_task.h"
#include "coe_drive_state_handler.h"
#include "word_bit.h"

void LonelyDriveMoveTask::SetTargetPosition(int32_t target_position)
{
	this->target_position_count = target_position;
}

void RealLonelyDriveMoveTask::StateRun()
{
	auto drive = GetContext()->GetSubsystem()->GetDrive();
	int64_t controlword = drive->GetRxPDOEntry("Controlword")->LoadValue();
	int64_t actual_position_count = drive->GetTxPDOEntry("Actual position")->LoadValue();
	int64_t mode_of_operation_out = drive->GetTxPDOEntry("Mode of operation out")->LoadValue();
	
	switch(this->task_state)
	{
		case 0:
		drive->GetRxPDOEntry("Mode of operation")->StoreValue(kModeProfilePosition);
		drive->GetRxPDOEntry("Target position")->StoreValue(this->target_position_count);
		WordBit::Write(&controlword, 8, 0);
		WordBit::Write(&controlword, 6, 0);		
		WordBit::Write(&controlword, 5, 1);	
		WordBit::Write(&controlword, 4, 0);

		if (mode_of_operation_out == kModeProfilePosition)
		{
			this->task_state++;
		}			
		break;
		case 1:
		WordBit::Write(&controlword, 4, 1);
		break;
	}

	if (actual_position_count == target_position_count)
	{
		WordBit::Write(&controlword, 4, 0);
		LonelyDriveTaskState::GetContext()->TransitToNext();
	}
	drive->GetRxPDOEntry("Controlword")->StoreValue(controlword);
}

void EmulatedLonelyDriveMoveTask::StateRun()
{}