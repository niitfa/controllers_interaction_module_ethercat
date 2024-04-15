#ifndef LONELYDRIVEENABLETASK_H
#define LONELYDRIVEENABLETASK_H

#include "lonely_drive.h"

class LonelyDriveEnableTask;
class RealLonelyDriveEnableTask;
class EmulatedLonelyDriveEnableTask;

class LonelyDriveEnableTask : public LonelyDriveTaskState, 
	public SubsystemStateSelector<
	LonelyDrive,
	LonelyDriveEnableTask,
	RealLonelyDriveEnableTask,
	EmulatedLonelyDriveEnableTask
	>
{
public:
	/* Общий интерфейс */
};

class RealLonelyDriveEnableTask : public LonelyDriveEnableTask
{
public:
	void StateRun() override;
};

class EmulatedLonelyDriveEnableTask : public LonelyDriveEnableTask
{
public:
	void StateRun() override;
};



#endif