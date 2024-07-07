#include <iostream>

#include "mklkt_network.h"
#include "gantry_stop_task.h"



int main(int argc,char** argv)
{
	MKLKTNetwork* network = new MKLKTNetwork();
	
	network->Build(0);
	network->StartThread();

	auto gantry_stop_task = GantryStopTask::CreateTaskFor(network->GetDevice()->GetGantry());
	network->GetDevice()->GetGantry()->SetTask(gantry_stop_task);

	while(true);

	return 0;
}
