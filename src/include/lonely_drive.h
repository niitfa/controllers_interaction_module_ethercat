#ifndef LONELYDRIVE_H
#define LONELYDRIVE_H

#include "subsystem.h"
#include "subsystem_state_selector.h"
#include "ethercat_slave.h"
#include "external_emulation_manager.h"


struct LonelyDriveTelemetry
{
	int32_t pds_state = 0;
	int32_t drive_position_count = 0;
	int32_t drive_velocity_count_per_sec = 0;	
};

class LonelyDrive;
class LonelyDriveTaskContext;
class LonelyDriveTaskState;

class LonelyDriveTaskState : public StateContentCreator<LonelyDriveTaskContext, LonelyDriveTaskState, LonelyDrive, LonelyDriveTelemetry>
{};
class LonelyDriveTaskContext : public ContextContentCreator<LonelyDriveTaskContext, LonelyDriveTaskState, LonelyDrive, LonelyDriveTelemetry>
{};

class LonelyDrive : public SubsystemContentCreator<LonelyDriveTaskContext, LonelyDriveTaskState, LonelyDrive, LonelyDriveTelemetry>
{
protected:
	EthercatSlave* drive = nullptr;
public:
	void RegisterDrive(EthercatSlave*);
	EthercatSlave* GetDrive();
};

class RealLonelyDrive : public LonelyDrive
{
public:
	bool IsEmulated() override { return false; }
	void ModifyTelemetry() override;
};

class EmulatedLonelyDrive : public LonelyDrive
{
public:
	bool IsEmulated() override { return true; }
	void ModifyTelemetry() override;
};

/* Emulations */

class LonelyDriveEmulation : public EmulatedEventContentCleator<LonelyDriveTaskContext>
{};

/* В отдельный файл!!! */
class TestEmulation : public LonelyDriveEmulation
{
	int cnt;
public:
	TestEmulation()
	{
		this->cnt = 0;
	}

	~TestEmulation()
	{
		//std::cout << "DELETED\n";
	}

	void RunEvent() override
	{
		//auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
		//telemetry->drive_position_count = cnt--;

		std::cout << "Emulated event " << ++cnt << "...\n";

		if(cnt == 100)
		{
			this->EndThisEvent();
		}
	}
};


#endif