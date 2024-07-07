#ifndef KV_DETECTOR_DRIVE_ENABLE_TASK_H
#define KV_DETECTOR_DRIVE_ENABLE_TASK_H

#include "kv_detector_drive.h"
#include "common_enable_drive_task.h"

class KVDetectorDriveEnableTask : public KVDetectorDriveTask, 
	public SubsystemStateSelector<KVDetectorDrive, 
    class KVDetectorDriveEnableTask, 
    class RealKVDetectorDriveEnableTask, 
    class EmulatedKVDetectorDriveEnableTask>
{
};

class EmulatedKVDetectorDriveEnableTask : public KVDetectorDriveEnableTask
{
public:
	void StateRun() override;
};

class RealKVDetectorDriveEnableTask : public KVDetectorDriveEnableTask
{
	CommonEnableDriveTask<KVDetectorDriveContext> task;
public:
	void StateRun() override;
};

#endif