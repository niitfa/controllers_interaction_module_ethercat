#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "ethercat_thread_builder.h"

#include "kv_filter_drive_move_to_limiter_task.h"
#include "kv_filter_drive_enable_task.h"

#include "kv_detector_drive_move_to_limiter_task.h"
#include "kv_detector_drive_enable_task.h"



int main(int argc,char** argv)
{
	//auto network = EthercatThreadBuilder::BuildThread_IOModule(0);
	//auto network = EthercatThreadBuilder::BuildThread_Drive(0);
	auto network = EthercatThreadBuilder::BuildThread_KVFiltDrive_IOModule_KVDetDrive(2);
	network.thread->StartThread();
	std::this_thread::sleep_for(std::chrono::milliseconds(150000));

	float filt_drive_velocity_mm_per_sec = 3;
	float det_drive_velocity_mm_per_sec = 5;

	bool run_kv_filter = 0;
	bool run_kv_detector = 1;

	/* Forming task chain */
	for (int i = 0; i < 3; ++i)
	{
		RealKVFilterDriveEnableTask* enable_task_filt;
		RealKVFilterDriveMoveToLimiterTask* move_lim_task_filt;

		RealKVDetectorDriveEnableTask* enable_task_det;
		RealKVDetectorDriveMoveToLimiterTask* move_lim_task_det;

		/* detector */
		if(run_kv_detector)
		{
			enable_task_det = new RealKVDetectorDriveEnableTask();
			move_lim_task_det = new RealKVDetectorDriveMoveToLimiterTask();

			move_lim_task_det->SetVelocity(-1 * det_drive_velocity_mm_per_sec);
			enable_task_det->WithNextTask(move_lim_task_det);
			network.kv_detector_drive->SetTask(enable_task_det);
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));

			move_lim_task_det = new RealKVDetectorDriveMoveToLimiterTask();
			move_lim_task_det->SetVelocity(0);
			network.kv_detector_drive->SetTask(move_lim_task_det);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			move_lim_task_det = new RealKVDetectorDriveMoveToLimiterTask();
			move_lim_task_det->SetVelocity(det_drive_velocity_mm_per_sec);
			network.kv_detector_drive->SetTask(move_lim_task_det);
			std::this_thread::sleep_for(std::chrono::milliseconds(4000));

			move_lim_task_det = new RealKVDetectorDriveMoveToLimiterTask();
			move_lim_task_det->SetVelocity(0);
			network.kv_detector_drive->SetTask(move_lim_task_det);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}	
		
		/*	filter	*/
		if(run_kv_filter)
		{
			enable_task_filt = new RealKVFilterDriveEnableTask();
			move_lim_task_filt = new RealKVFilterDriveMoveToLimiterTask();
			move_lim_task_filt->SetVelocity(-1 * filt_drive_velocity_mm_per_sec);
			enable_task_filt->WithNextTask(move_lim_task_filt);
			network.kv_filter_drive->SetTask(enable_task_filt);
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}

		/* filter */
		if(run_kv_filter)
		{
			move_lim_task_filt = new RealKVFilterDriveMoveToLimiterTask();
			move_lim_task_filt->SetVelocity(0);
			network.kv_filter_drive->SetTask(move_lim_task_filt);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		
		/* filter */
		if(run_kv_filter)
		{
			move_lim_task_filt = new RealKVFilterDriveMoveToLimiterTask();
			move_lim_task_filt->SetVelocity(filt_drive_velocity_mm_per_sec);
			network.kv_filter_drive->SetTask(move_lim_task_filt);
			std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		}


		/* filter */
		if(run_kv_filter)
		{
			move_lim_task_filt = new RealKVFilterDriveMoveToLimiterTask();
			move_lim_task_filt->SetVelocity(0);
			network.kv_filter_drive->SetTask(move_lim_task_filt);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}


	//network.kv_drive->SetTask(enable_task);
	while(1)
	{}
	network.thread->StopThread();
	return 0;
}
