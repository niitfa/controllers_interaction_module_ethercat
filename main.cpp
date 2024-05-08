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
#include "calculation_task.h"
//#include "lonely_drive.h"
#include "real_lonely_drive.h"
#include "emulated_lonely_drive.h"
#include "lonely_drive_test_emulation.h"

#include "gantry.h"
#include "gantry_enable_task.h"

//#include "ethercat_thread_factory.h"
#include "ethercat_thread_builder.h"
#include "external_emulation_manager.h"


#include "unspecified_device.h"
#include "real_lonely_drive.h"



int main(int argc,char** argv)
{
	EthercatThreadBuilder::IOModuleThreadContent network = EthercatThreadBuilder::BuildThread_IOModule(0);
	network.thread->StartThread();
	while(1)
	{}

	return 0;
}
