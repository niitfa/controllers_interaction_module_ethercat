#ifndef LONELY_DRIVE_MOVE_TASK_H
#define LONELY_DRIVE_MOVE_TASK_H

#include "lonely_drive.h"

class LonelyDriveMoveTask : public LonelyDriveTaskState, 
	public SubsystemStateSelector<LonelyDrive, class LonelyDriveMoveTask, class RealLonelyDriveMoveTask, class EmulatedLonelyDriveMoveTask>
{
public:
	LonelyDriveMoveTask();
	void SetTargetPosition(int32_t);	
protected:
	int32_t target_position_count;	
	int task_state;
};

#endif