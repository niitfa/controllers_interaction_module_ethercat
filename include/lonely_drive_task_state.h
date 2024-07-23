#ifndef LONELY_DRIVE_TASK_STATE_H
#define LONELY_DRIVE_TASK_STATE_H

#include "state_content_creator.h"
#include "lonely_drive_telemetry.h"

class LonelyDriveTaskState : public StateContentCreator<class LonelyDriveTaskContext, class LonelyDriveTaskState, class LonelyDrive, LonelyDriveTelemetry>
{};

#endif