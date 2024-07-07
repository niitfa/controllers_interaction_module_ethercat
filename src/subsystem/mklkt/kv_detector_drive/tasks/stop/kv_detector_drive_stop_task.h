#ifndef KV_DETECTOR_DRIVE_STOP_TASK_H
#define KV_DETECTOR_DRIVE_STOP_TASK_H

#include "kv_detector_drive.h"
#include "common_stop_drive_task.h"

class KVDetectorDriveStopTask : public KVDetectorDriveTask, 
	public SubsystemStateSelector<KVDetectorDrive, class KVDetectorDriveStopTask, class RealKVDetectorDriveStopTask, class EmulatedKVDetectorDriveStopTask>
{
};

class EmulatedKVDetectorDriveStopTask : public KVDetectorDriveStopTask
{
public:
	void StateRun() override;
};

class RealKVDetectorDriveStopTask : public KVDetectorDriveStopTask
{
	CommonStopDriveTask<KVDetectorDriveContext> task;
public:
	void StateRun() override;
};


#endif