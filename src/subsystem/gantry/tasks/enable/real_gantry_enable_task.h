#ifndef REAL_GANTRY_ENABLE_TASK_H
#define REAL_GANTRY_ENABLE_TASK_H

#include "gantry_enable_task.h"

class RealGantryEnableTask : public GantryEnableTask
{
public:
	void StateRun() override;
};

#endif