#ifndef CALCULATION_TASK_H
#define CALCULATION_TASK_H

#include "lonely_drive.h"

class CalculationTask : public LonelyDriveTaskState, 
	public SubsystemStateSelector<LonelyDrive, class CalculationTask, class CalculationTask, class CalculationTask>
{
    void StateRun() override;
};


#endif