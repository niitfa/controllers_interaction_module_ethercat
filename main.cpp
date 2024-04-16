#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "device_model.h"
#include "ethercat_thread_manager.h"
#include "ethercat_configuration.h"

#include "lonely_drive_enable_task.h"
#include "lonely_drive_move_task.h"
#include "lonely_drive.h"

#include "gantry.h"
#include "gantry_enable_task.h"

#include "ethercat_thread_configurator.h"

#include "external_emulation_manager.h"

int pCharToInt(char* value)
{
	std::stringstream strValue;
	strValue << value;
	int intValue;
	strValue >> intValue;
	
	return intValue;
}


int main(int argc,char** argv)
{
	int chanched;

	/*EthercatThreadManager* ethercat_thread_0 = new EthercatThreadManager();
	TorusModel* torus_0 = new TorusModel();

	ConfigureEthercatThread_gantry(ethercat_thread_0, torus_0);
	ethercat_thread_0->StartThread();	
	auto gantry = torus_0->GetGantry();
	GantryEnableTask* gantry_enable = GantryEnableTask::CreateTaskFor(gantry);
	torus_0->GetGantry()->SetTask(gantry_enable);

	std::chrono::milliseconds sleep_time(1);
	while (1)
	{
		auto gantry_pos = torus_0->GetGantry()->GetTelemetry()->gantry_position_count;
		auto gantry_vel = torus_0->GetGantry()->GetTelemetry()->gantry_velocity_count_per_sec;
		//std::cout << "Main thread gantry_pos: " << gantry_pos << std::endl;
		std::cout << "Main thread gantry_vel: " << gantry_vel << std::endl;
		torus_0->UpdateTelemetry();
		std::this_thread::sleep_for(sleep_time);
	} */

	// PREV
	EthercatThreadManager* ethercat_thread_0 = new EthercatThreadManager();
	UnspecifiedDevice* device_0 = new UnspecifiedDevice();
	LonelyDrive* mech_subsystem_0 = new RealLonelyDrive();
	ConfigureNetwork_0(ethercat_thread_0, device_0, mech_subsystem_0);

	EthercatThreadManager* ethercat_thread_1 = new EthercatThreadManager();
	UnspecifiedDevice* device_1 = new UnspecifiedDevice();
	LonelyDrive* mech_subsystem_1 = new RealLonelyDrive();
	ConfigureNetwork_1(ethercat_thread_1, device_1, mech_subsystem_1);

	//ethercat_thread_0->StartThread();
	ethercat_thread_1->StartThread();

	std::chrono::milliseconds sleep_time(500);
	std::this_thread::sleep_for(sleep_time); 

	// PREV

	//TestEmulation* emul = new TestEmulation();

	while(1)
	{
		TestEmulation* emul = new TestEmulation();
		mech_subsystem_1->InsertEmulationEvent(emul);
		std::this_thread::sleep_for(sleep_time);
		//mech_subsystem_1->ClearAllEmulationEvents();	
		//mech_subsystem_1->RemoveEmulationEvent(emul);
	}

	/*mech_subsystem_1->GetEmulationManager()->InsertEvent(emul);
	std::this_thread::sleep_for(sleep_time);
	mech_subsystem_1->GetEmulationManager()->RemoveEvent(emul);
	std::this_thread::sleep_for(sleep_time);
	mech_subsystem_1->GetEmulationManager()->InsertEvent(emul);
	std::this_thread::sleep_for(sleep_time);
	mech_subsystem_1->GetEmulationManager()->RemoveEvent(emul); */

	/* Task from command line */
	/*while(true)
	{
		int32_t pos_0, pos_1;
		std::cout << "Enter drive 0 (HIWIN) position:\n> ";
		std::cin >> pos_0;
		std::cout << "Enter drive 1 (LEADSHINE) position:\n> ";	
		std::cin >> pos_1;
		std::cout << "Moving...\n\n";

		LonelyDriveEnableTask* enable_drive_0 = LonelyDriveEnableTask::CreateTaskFor(mech_subsystem_0);
		LonelyDriveMoveTask* move_drive_0 = LonelyDriveMoveTask::CreateTaskFor(mech_subsystem_0);
		move_drive_0->SetTargetPosition(pos_0);
		LonelyDriveTaskState::StartQueueWith(enable_drive_0)
			->WithNextTask(move_drive_0);
		mech_subsystem_0->SetTask(enable_drive_0);

		LonelyDriveEnableTask* enable_drive_1 = LonelyDriveEnableTask::CreateTaskFor(mech_subsystem_1);
		LonelyDriveMoveTask* move_drive_1 = LonelyDriveMoveTask::CreateTaskFor(mech_subsystem_1);
		move_drive_1->SetTargetPosition(pos_1);
		LonelyDriveTaskState::StartQueueWith(enable_drive_1)
			->WithNextTask(move_drive_1);
		mech_subsystem_1->SetTask(enable_drive_1);	
	} */

	
	std::chrono::milliseconds sleep_time_2(100);
	/*while(1)
	{
		device_0->UpdateTelemetry();
		auto telemetry = device_0->GetEthercatConfig()->GetTelemetry();
		std::cout << "wkc: " << (uint16_t)telemetry->domain_state.working_counter << std::endl;
		//std::cout << (uint16_t)telemetry->slaves_info[0].al_state << std::endl;
		std::this_thread::sleep_for(sleep_time_2);	
	} */


	while(1)
	{}

	return 0;
}
