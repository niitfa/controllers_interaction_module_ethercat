#ifndef REAL_DRIVE_MOVE_TASK_H
#define REAL_DRIVE_MOVE_TASK_H

#include "lonely_drive_move_task.h"

class RealLonelyDriveMoveTask : public LonelyDriveMoveTask
{
public:
	void StateRun() override;
};

#endif