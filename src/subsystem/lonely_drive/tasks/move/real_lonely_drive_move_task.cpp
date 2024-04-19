#include "real_lonely_drive_move_task.h"
#include "coe_drive_state_handler.h"
#include "word_bit.h"
#include "coe_object_names.h"

using namespace coe_drive_state_handler;
using namespace coe_object_names;

void RealLonelyDriveMoveTask::StateRun()
{
	auto drive = GetContext()->GetSubsystem()->GetDrive();
	int64_t controlword = drive->GetRxPDOEntry(kControlword)->LoadValue();
	int64_t actual_position_count = drive->GetTxPDOEntry(kActualPosition)->LoadValue();
	int64_t mode_of_operation_out = drive->GetTxPDOEntry(kModeOfOperationOut)->LoadValue();
	
	switch(this->task_state)
	{
		case 0:
		drive->GetRxPDOEntry(kModeOfOperation)->StoreValue(kModeProfilePosition);
		drive->GetRxPDOEntry(kTargetPosition)->StoreValue(this->target_position_count);
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
	drive->GetRxPDOEntry(kControlword)->StoreValue(controlword);
}