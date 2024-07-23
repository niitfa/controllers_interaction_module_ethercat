#ifndef KV_FILTER_DRIVE_ENABLE_TASK_H
#define KV_FILTER_DRIVE_ENABLE_TASK_H

#include "kv_filter_drive.h"
#include "common_enable_drive_task.h"

class KVFilterDriveEnableTask : public KVFilterDriveTask, 
	public SubsystemStateSelector<KVFilterDrive, class KVFilterDriveEnableTask, class RealKVFilterDriveEnableTask, class EmulatedKVFilterDriveEnableTask>
{
};

class EmulatedKVFilterDriveEnableTask : public KVFilterDriveEnableTask
{
	const int kEnablingDelayCycles = 30;
	int delay_counter = 0;
public:
	EmulatedKVFilterDriveEnableTask();
	void StateRun() override;
};

class RealKVFilterDriveEnableTask : public KVFilterDriveEnableTask
{
	CommonEnableDriveTask<KVFilterDriveContext> task;
public:
	void StateRun() override;
};

#endif