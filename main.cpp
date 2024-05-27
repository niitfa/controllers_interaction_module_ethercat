#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "ethercat_thread_builder.h"

#include "kv_filter_drive_move_to_limiter_task.h"
#include "kv_filter_drive_enable_task.h"



int main(int argc,char** argv)
{
	//auto network = EthercatThreadBuilder::BuildThread_IOModule(0);
	//auto network = EthercatThreadBuilder::BuildThread_Drive(0);
	auto network = EthercatThreadBuilder::BuildThread_Drive_IOModule(0);
	network.thread->StartThread();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	/* Forming task chain */
	RealKVFilterDriveEnableTask* enable_task = new RealKVFilterDriveEnableTask();
	RealKVFilterDriveMoveToLimiterTask* move_lim_task = new RealKVFilterDriveMoveToLimiterTask();
	move_lim_task->SetVelocity(-2);
	//move_lim_task->SavePropertiesOf(network.kv_drive);
	enable_task->WithNextTask(move_lim_task);

	network.kv_drive->SetTask(enable_task);
	while(1)
	{}
	network.thread->StopThread();
	return 0;
}
