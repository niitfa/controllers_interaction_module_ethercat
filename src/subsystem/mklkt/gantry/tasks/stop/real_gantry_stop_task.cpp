#include "gantry_stop_task.h"

void RealGantryStopTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}