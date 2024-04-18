#ifndef REAL_LONELY_DRIVE_ENABLE_TASK_H
#define REAL_LONELY_DRIVE_ENABLE_TASK_H

#include "lonely_drive_enable_task.h"

class RealLonelyDriveEnableTask : public LonelyDriveEnableTask
{
public:
	void StateRun() override;
};


#endif