#ifndef LONELYDRIVEMOVETASK_H
#define LONELYDRIVEMOVETASK_H

#include "lonely_drive.h"

class LonelyDriveMoveTask;
class RealLonelyDriveMoveTask;
class EmulatedLonelyDriveMoveTask;

class LonelyDriveMoveTask : public LonelyDriveTaskState, 
	public SubsystemStateSelector<
		LonelyDrive,
		LonelyDriveMoveTask,
		RealLonelyDriveMoveTask,
		EmulatedLonelyDriveMoveTask
	>
{

public:
	void SetTargetPosition(int32_t);	
protected:
	int32_t target_position_count = 0;	
	int task_state = 0;
};

class RealLonelyDriveMoveTask : public LonelyDriveMoveTask
{
public:
	void StateRun() override;
};

class EmulatedLonelyDriveMoveTask : public LonelyDriveMoveTask
{
public:
	void StateRun() override;
};

#endif