#ifndef LONELY_DRIVE_TASK_CONTEXT_H
#define LONELY_DRIVE_TASK_CONTEXT_H

#include "context_content_creator.h"
#include "lonely_drive_telemetry.h"

class LonelyDriveTaskContext : public ContextContentCreator<class LonelyDriveTaskContext, class LonelyDriveTaskState, class LonelyDrive, LonelyDriveTelemetry>
{
};

#endif