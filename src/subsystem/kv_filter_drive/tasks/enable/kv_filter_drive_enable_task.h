#ifndef KV_FILTER_DRIVE_ENABLE_TASK_H
#define KV_FILTER_DRIVE_ENABLE_TASK_H

#include "kv_filter_drive.h"

class KVFilterDriveEnableTask : public KVFilterDriveTask, 
	public SubsystemStateSelector<KVFilterDrive, class KVFilterDriveEnableTask, class RealKVFilterDriveEnableTask, class EmulatedKVFilterDriveEnableTask>
{
};

class EmulatedKVFilterDriveEnableTask : public KVFilterDriveEnableTask
{
public:
	void StateRun() override;
};

class RealKVFilterDriveEnableTask : public KVFilterDriveEnableTask
{
public:
	void StateRun() override;
};

#endif