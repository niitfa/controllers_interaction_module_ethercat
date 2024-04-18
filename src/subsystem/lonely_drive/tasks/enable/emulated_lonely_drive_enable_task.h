#ifndef EMULATED_LONELY_DRIVE_ENABLE_TASK_H
#define EMULATED_LONELY_DRIVE_ENABLE_TASK_H

#include "lonely_drive_enable_task.h"

class EmulatedLonelyDriveEnableTask : public LonelyDriveEnableTask
{
public:
	void StateRun() override;
};


#endif