#include "kv_detector_drive_enable_task.h"

void RealKVDetectorDriveEnableTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}