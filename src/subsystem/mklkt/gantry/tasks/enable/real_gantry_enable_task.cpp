#include "gantry_enable_task.h"

void RealGantryEnableTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}