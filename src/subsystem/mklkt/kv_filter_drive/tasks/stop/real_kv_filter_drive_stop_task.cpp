#include "kv_filter_drive_stop_task.h"

void RealKVFilterDriveStopTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}