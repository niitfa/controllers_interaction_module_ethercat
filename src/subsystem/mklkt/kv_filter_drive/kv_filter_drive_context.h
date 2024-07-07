#ifndef KV_FILTER_DRIVE_CONTEXT_H
#define KV_FILTER_DRIVE_CONTEXT_H

#include "context_content_creator.h"
#include "kv_filter_drive_telemetry.h"

class KVFilterDriveContext : public ContextContentCreator<class KVFilterDriveContext, class KVFilterDriveTask, class KVFilterDrive, KVFilterDriveTelemetry>
{};

#endif