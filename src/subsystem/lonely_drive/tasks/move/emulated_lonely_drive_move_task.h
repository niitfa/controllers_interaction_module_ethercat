#ifndef EMULATED_DRIVE_MOVE_TASK_H
#define EMULATED_DRIVE_MOVE_TASK_H

#include "lonely_drive_move_task.h"

class EmulatedLonelyDriveMoveTask : public LonelyDriveMoveTask
{
public:
	void StateRun() override;
};

#endif