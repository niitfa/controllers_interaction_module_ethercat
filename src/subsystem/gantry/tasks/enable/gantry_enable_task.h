#ifndef GANTRY_ENABLE_TASK_H
#define GANTRY_ENABLE_TASK_H

#include "gantry.h"

class GantryEnableTask : public GantryTaskState, 
	public SubsystemStateSelector<Gantry, class GantryEnableTask, class RealGantryEnableTask, class EmulatedGantryEnableTask>
{
public:
	virtual ~GantryEnableTask() = default;
	/* Общий интерфейс */
};

class EmulatedGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};

class RealGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};


#endif