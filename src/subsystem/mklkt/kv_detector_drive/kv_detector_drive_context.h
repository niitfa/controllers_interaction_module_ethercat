#ifndef KV_DETECTOR_DRIVE_CONTEXT_H
#define KV_DETECTOR_DRIVE_CONTEXT_H

#include "context_content_creator.h"
#include "kv_detector_drive_telemetry.h"

class KVDetectorDriveContext : public ContextContentCreator<class KVDetectorDriveContext, class KVDetectorDriveTask, class KVDetectorDrive, KVDetectorDriveTelemetry>
{};

#endif