#ifndef KV_DETECTOR_DRIVE_TASK_H
#define KV_DETECTOR_DRIVE_TASK_H

#include "state_content_creator.h"
#include "kv_detector_drive_telemetry.h"

class KVDetectorDriveTask : public StateContentCreator<class KVDetectorDriveContext, class KVDetectorDriveTask, class KVDetectorDrive, KVDetectorDriveTelemetry>
{
};

#endif