#include "ethercat_thread_manager.h"
#include "stopwatch.h"
#include "cycle_tester.h"

EthercatThreadManager::EthercatThreadManager()
{
	is_launched.store(false);
}

EthercatThreadManager::~EthercatThreadManager()
{
	delete device;
}

void EthercatThreadManager::RegisterDevice(DeviceModel* dev)
{
	this->device = dev;
}

void EthercatThreadManager::StartThread()
{
	if (!is_launched.load() && device)
	{
		is_initialized.store(false);
		is_stop_forced.store(false);
		is_launched.store(true);
		std::thread thrd(&EthercatThreadManager::Handler, this);
		if(!this->cpus.empty())
		{
			cpu_set_t cpuset;
			CPU_ZERO(&cpuset);
			for(auto cpu : this->cpus)
			{
				CPU_SET(cpu, &cpuset);
			}
			int rc = pthread_setaffinity_np(thrd.native_handle(), sizeof(cpuset), &cpuset);

			//sched_param param;
			//param.sched_priority = 20;
			//pthread_setschedparam(thrd.native_handle(), SCHED_FIFO, &param);
		}
		thrd.detach();
		WaitForInit();
	}
}

void EthercatThreadManager::StopThread()
{
	is_stop_forced.store(true);
	while(is_launched.load()) {}
}

void EthercatThreadManager::Handler()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if (this->device)
	{
		//Stopwatch stopwatch;
		auto ethercat_config = device->GetEthercatConfig();
		ethercat_config->Initialize();
		is_initialized.store(true);
		/* App time*/
		ecrt_master_application_time(ethercat_config->GetMaster()->GetRequest(), ethercat_config->GetTimer()->GetCurrentTime());
		while (!is_stop_forced.load())
		{
			//stopwatch.Reset();
			ethercat_config->GetTimer()->Sleep();
			//stopwatch.Update();
			//std::cout << "EthercatThreadManager::Handler(): " << stopwatch.Nanoseconds() <<std::endl;	
			ethercat_config->PreProcessingAction();
			device->Action();
			ethercat_config->PostProcessingAction();

		}
		ethercat_config->Release();
	}
	else
	{
		is_initialized.store(true);
	}
	is_launched.store(false);
}

void EthercatThreadManager::WaitForInit()
{
	while (!is_initialized.load()) {}
}

void EthercatThreadManager::SetCPUs(std::vector<int> cpus)
{
	this->cpus = cpus;
} 
