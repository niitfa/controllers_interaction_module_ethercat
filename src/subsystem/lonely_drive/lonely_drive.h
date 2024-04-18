#ifndef LONELYDRIVE_H
#define LONELYDRIVE_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"
#include "ethercat_slave.h"

#include "lonely_drive_telemetry.h"
#include "lonely_drive_task_state.h"
#include "lonely_drive_task_context.h"


class LonelyDrive : public SubsystemContentCreator<LonelyDriveTaskContext, LonelyDriveTaskState, LonelyDrive, LonelyDriveTelemetry>
{
protected:
	EthercatSlave* drive = nullptr;
public:
	void RegisterDrive(EthercatSlave*);
	EthercatSlave* GetDrive();
};

#endif