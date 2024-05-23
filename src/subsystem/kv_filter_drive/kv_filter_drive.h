#ifndef KV_FILTER_DRIVE_H
#define KV_FILTER_DRIVE_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "kv_filter_drive_telemetry.h"
#include "kv_filter_drive_task.h"
#include "kv_filter_drive_context.h"

class KVFilterDrive : public SubsystemContentCreator<KVFilterDriveContext, KVFilterDriveTask, KVFilterDrive, KVFilterDriveTelemetry>
{

};

#endif