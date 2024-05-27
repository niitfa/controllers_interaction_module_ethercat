#ifndef KV_FILTER_DRIVE_TASK_H
#define KV_FILTER_DRIVE_TASK_H

#include "state_content_creator.h"
#include "kv_filter_drive_telemetry.h"

class KVFilterDriveTask : public StateContentCreator<class KVFilterDriveContext, class KVFilterDriveTask, class KVFilterDrive, KVFilterDriveTelemetry>
{
};

#endif