#include "lonely_drive_move_task.h"
#include "coe_drive_state_handler.h"
#include "word_bit.h"

LonelyDriveMoveTask::LonelyDriveMoveTask()
{
	this->target_position_count = 0;
	this->task_state = 0;
}

void LonelyDriveMoveTask::SetTargetPosition(int32_t target_position)
{
	this->target_position_count = target_position;
}