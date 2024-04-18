#ifndef LONELY_DRIVE_ENABLE_TASK_H
#define LONELY_DRIVE_ENABLE_TASK_H

#include "lonely_drive.h"

class LonelyDriveEnableTask : public LonelyDriveTaskState, 
	public SubsystemStateSelector<LonelyDrive, class LonelyDriveEnableTask, class RealLonelyDriveEnableTask, class EmulatedLonelyDriveEnableTask>
{
};

#endif