#include "kv_detector_drive_stop_task.h"

void RealKVDetectorDriveStopTask::StateRun()
{
	if(GetContext()->GetSubsystem()->GetDrive())
	{
		task.RunTask(GetContext());
	}
}