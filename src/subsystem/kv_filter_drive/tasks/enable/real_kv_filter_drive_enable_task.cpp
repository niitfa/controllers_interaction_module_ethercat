#include "kv_filter_drive_enable_task.h"

void RealKVFilterDriveEnableTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}