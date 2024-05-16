#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "ethercat_thread_builder.h"




int main(int argc,char** argv)
{
	EthercatThreadBuilder::IOModuleThreadContent network = EthercatThreadBuilder::BuildThread_IOModule(0);
	network.thread->StartThread();
	while(1)
	{}

	return 0;
}
