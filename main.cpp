#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "ethercat_thread_builder.h"



int main(int argc,char** argv)
{
	//auto network = EthercatThreadBuilder::BuildThread_IOModule(0);
	//auto network = EthercatThreadBuilder::BuildThread_Drive(0);
	auto network = EthercatThreadBuilder::BuildThread_Drive_IOModule(0);
	network.thread->StartThread();
	//std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	while(1)
	{}
	network.thread->StopThread();
	return 0;
}
