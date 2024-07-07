#ifndef GANTRY_STOP_TASK_H
#define GANTRY_STOP_TASK_H

#include "gantry.h"
#include "common_stop_drive_task.h"

class GantryStopTask : public GantryTaskState, 
	public SubsystemStateSelector<Gantry, class GantryStopTask, class RealGantryStopTask, class EmulatedGantryStopTask>
{
};

class EmulatedGantryStopTask : public GantryStopTask
{
public:
	void StateRun() override;
};

class RealGantryStopTask : public GantryStopTask
{
	CommonStopDriveTask<GantryTaskContext> task;
public:
	void StateRun() override;
};


#endif