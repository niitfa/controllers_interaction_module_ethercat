#ifndef KV_FILTER_DRIVE_STOP_TASK_H
#define KV_FILTER_DRIVE_STOP_TASK_H

#include "kv_filter_drive.h"
#include "common_stop_drive_task.h"

class KVFilterDriveStopTask : public KVFilterDriveTask, 
	public SubsystemStateSelector<KVFilterDrive, class KVFilterDriveStopTask, class RealKVFilterDriveStopTask, class EmulatedKVFilterDriveStopTask>
{
};

class EmulatedKVFilterDriveStopTask : public KVFilterDriveStopTask
{
public:
	void StateRun() override;
};

class RealKVFilterDriveStopTask : public KVFilterDriveStopTask
{
	CommonStopDriveTask<KVFilterDriveContext> task;
public:
	void StateRun() override;
};


#endif