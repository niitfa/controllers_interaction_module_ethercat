#ifndef GANTRYENABLETASK_H
#define GANTRYENABLETASK_H

#include "gantry.h"

class GantryEnableTask;
class RealGantryEnableTask;
class EmulatedGantryEnableTask;

class GantryEnableTask : public GantryTaskState, 
	public SubsystemStateSelector<
	Gantry,
	GantryEnableTask,
	RealGantryEnableTask,
	EmulatedGantryEnableTask
	>
{
public:
	virtual ~GantryEnableTask() = default;
	/* Общий интерфейс */
};

class RealGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};

class EmulatedGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};




#endif