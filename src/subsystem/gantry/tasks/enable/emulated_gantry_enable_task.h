#ifndef EMULATED_GANTRY_ENABLE_TASK_H
#define EMULATED_GANTRY_ENABLE_TASK_H

#include "gantry_enable_task.h"

class EmulatedGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};

#endif