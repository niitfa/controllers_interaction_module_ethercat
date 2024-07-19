#ifndef GANTRY_ENABLE_TASK_H
#define GANTRY_ENABLE_TASK_H

#include "gantry.h"
#include "common_enable_drive_task.h"

class GantryEnableTask : public GantryTaskState, 
	public SubsystemStateSelector<Gantry, class GantryEnableTask, class RealGantryEnableTask, class EmulatedGantryEnableTask>
{
};

class EmulatedGantryEnableTask : public GantryEnableTask
{
	const int kEnablingDelayCycles = 50;
	int delay_counter = 0;
public:
	EmulatedGantryEnableTask();
	void StateRun() override;
};

class RealGantryEnableTask : public GantryEnableTask
{
	CommonEnableDriveTask<GantryTaskContext> task;
public:
	void StateRun() override;
};


#endif