#include <iostream>

#include "mklkt_network.h"
#include "gantry_stop_task.h"
#include "gantry_enable_task.h"
#include "gantry_move_task.h"


int main(int argc,char** argv)
{
	MKLKTNetwork* network = new MKLKTNetwork();
	
	network->Build(0);
	network->StartThread();

	auto gantry = network->GetDevice()->GetGantry();

	float pos = 50;

	while(true)
	{
		network->GetDevice()->UpdateTelemetry();
		std::cout << "main(): gantry pos: " << gantry->GetTelemetry()->gantry_position_count << std::endl;
		/* Создаем 3 задания: включить, поехать, остановиться */
		auto gantry_enable_task = GantryEnableTask::CreateTaskFor(gantry);
		auto gantry_move_task = GantryMoveTask::CreateTaskFor(gantry);
		gantry_move_task->SetTargetPosition(50);
		gantry_move_task->SetVelocity(5);
		auto gantry_stop_task = GantryStopTask::CreateTaskFor(gantry);

		/* Создаем цепочку заданий включить + поехать */
		gantry_enable_task->WithNextTask(gantry_move_task);

		/* Запускаем задание включить + поехать */
		gantry->SetTask(gantry_enable_task);

		/* Едем некоторое время */
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		/* Запускаем задание остановиться */
		gantry->SetTask(gantry_stop_task);

		/* Стоим некоторое время */
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		/*  Меняем направление и повторяем */
		pos = -pos;
	}


	

	while(true);

	return 0;
}
