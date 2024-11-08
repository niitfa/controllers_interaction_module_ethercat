#include <iostream>

#include "mklkt_network.h"

#include "gantry_stop_task.h"
#include "gantry_enable_task.h"
#include "gantry_move_task.h"

#include "kv_detector_drive_enable_task.h"
#include "kv_detector_drive_move_task.h"
#include "kv_detector_drive_stop_task.h"

#include "kv_filter_drive_enable_task.h"
#include "kv_filter_drive_move_task.h"
#include "kv_filter_drive_stop_task.h"

void test()
{

	MKLKTNetwork* network = new MKLKTNetwork();

	//network->SetGantryEmulationStatus(true);
	network->SetKVDetectorDriveEmulatonStatus(true);
	network->SetKVFilterDriveEmulatonStatus(true);
	
	network->Build(0);
	network->StartThread();

	auto gantry = network->GetDevice()->GetGantry();
	auto kv_detector = network->GetDevice()->GetKVDetectorDrive();
	auto kv_filter = network->GetDevice()->GetKVFilterDrive();



	while(1)
	{
		network->GetDevice()->UpdateTelemetry();
		std::cout << "Gantry: "
		<< " enc_cnt: " << gantry->GetTelemetry()->drive_encoder_value_deg
		<< "\tenc_deg: " <<  gantry->GetTelemetry()->drive_encoder_value_deg
		<< "\tlim_sw: " <<  gantry->GetTelemetry()->limit_switch_homing_negative
		<< gantry->GetTelemetry()->limit_switch_homing_positive
		<< gantry->GetTelemetry()->limit_switch_user_positive
		<< gantry->GetTelemetry()->limit_switch_user_negative
		<< "\tpos: " <<  gantry->GetTelemetry()->drive_position_deg
		//<< "\tvel_count_per_sec: " <<  network->GetDevice()->GetGantry()->GetTelemetry()->drive_velocity_pulse_per_sec
		<< "\n";

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}


int main(int argc,char** argv)
{
	test();

	MKLKTNetwork* network = new MKLKTNetwork();

	//network->SetGantryEmulationStatus(true);
	network->SetKVDetectorDriveEmulatonStatus(true);
	network->SetKVFilterDriveEmulatonStatus(true);
	
	network->Build(0);
	network->StartThread();

	auto gantry = network->GetDevice()->GetGantry();
	auto kv_detector = network->GetDevice()->GetKVDetectorDrive();
	auto kv_filter = network->GetDevice()->GetKVFilterDrive();


		/* Цепочка заданий для гантри */
		auto gantry_enable_task = GantryEnableTask::CreateTaskFor(gantry);
		auto gantry_move_task = GantryMoveTask::CreateTaskFor(gantry);
		gantry_move_task->SetTargetPosition(5);
		gantry_move_task->SetVelocity(1);
		auto gantry_move_task_2 = GantryMoveTask::CreateTaskFor(gantry);
		gantry_move_task_2->SetTargetPosition(0);
		gantry_move_task_2->SetVelocity(0.5);
		gantry_enable_task->WithNextTask(gantry_move_task)->WithNextTask(gantry_move_task_2);
		gantry->SetTask(gantry_enable_task);

		/* Цепочка заданий для кВ детектора */

		auto kv_detector_enable_task = KVDetectorDriveEnableTask::CreateTaskFor(kv_detector);
		auto kv_detector_move_task = KVDetectorDriveMoveTask::CreateTaskFor(kv_detector);
		kv_detector_move_task->SetTargetPosition(20);
		kv_detector_move_task->SetVelocity(3);
		auto kv_detector_move_task_2 = KVDetectorDriveMoveTask::CreateTaskFor(kv_detector);
		kv_detector_move_task_2->SetTargetPosition(-10);
		kv_detector_move_task_2->SetVelocity(5);
		kv_detector_enable_task->WithNextTask(kv_detector_move_task)->WithNextTask(kv_detector_move_task_2);
		kv_detector->SetTask(kv_detector_enable_task);

		/* Цепочка заданий для кВ фильтра */
		auto kv_filter_enable_task = KVFilterDriveEnableTask::CreateTaskFor(kv_filter);
		auto kv_filter_move_task = KVFilterDriveMoveTask::CreateTaskFor(kv_filter);
		kv_filter_move_task->SetTargetPosition(4);
		kv_filter_move_task->SetVelocity(1);
		auto kv_filter_move_task_2 = KVFilterDriveMoveTask::CreateTaskFor(kv_filter);
		kv_filter_move_task_2->SetTargetPosition(3.5);
		kv_filter_move_task_2->SetVelocity(0.1);
		kv_filter_enable_task->WithNextTask(kv_filter_move_task)->WithNextTask(kv_filter_move_task_2);
		kv_filter->SetTask(kv_filter_enable_task);

		/* Вывод телеметрии в командную строку */
		while (true)
		{
			network->GetDevice()->UpdateTelemetry();
			/* Enable test */
			/*std::cout << "Devices enabled: "
				<< network->GetDevice()->GetGantry()->GetTelemetry()->is_drive_enabled 
				<< network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->is_drive_enabled
				<< network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->is_drive_enabled 
				<< std::endl; */

			/* Gantry move test */
			std::cout << "Gantry: "
				<< "\tenabled: " << network->GetDevice()->GetGantry()->GetTelemetry()->is_drive_enabled
				<< "\tpos_deg: " <<  network->GetDevice()->GetGantry()->GetTelemetry()->drive_position_deg
				<< "\tpos_count: " <<  network->GetDevice()->GetGantry()->GetTelemetry()->drive_position_pulse
				<< "\tvel_deg_per_sec: " <<  network->GetDevice()->GetGantry()->GetTelemetry()->drive_velocity_deg_per_sec
				<< "\tvel_count_per_sec: " <<  network->GetDevice()->GetGantry()->GetTelemetry()->drive_velocity_pulse_per_sec
				<< "\n";

			/* kV detector move test */
			/* std::cout << "kV det: "
				<< "\tenabled: " << network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->is_drive_enabled
				<< "\tpos_mm: " <<  network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->drive_position_mm
				<< "\tpos_count: " <<  network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->drive_position_pulse
				<< "\tvel_mm_per_sec: " <<  network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->drive_velocity_mm_per_sec
				<< "\tvel_count_per_sec: " <<  network->GetDevice()->GetKVDetectorDrive()->GetTelemetry()->drive_velocity_pulse_per_sec
				<< "\n"; */

			/* kV filter move test */
			/* std::cout << "kV filt: "
				<< "\tenabled: " << network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->is_drive_enabled
				<< "\tpos_mm: " <<  network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->drive_position_mm
				<< "\tpos_count: " <<  network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->drive_position_pulse
				<< "\tvel_mm_per_sec: " <<  network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->drive_velocity_mm_per_sec
				<< "\tvel_count_per_sec: " <<  network->GetDevice()->GetKVFilterDrive()->GetTelemetry()->drive_velocity_pulse_per_sec
				<< "\n"; */

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

	return 0;
}

