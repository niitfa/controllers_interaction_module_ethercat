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
	if (this->device)
	{
		auto ethercat_config = device->GetEthercatConfig();
		ethercat_config->Initialize();
		is_initialized.store(true);

		/* Логирование свойств цикла */
		uint32_t size = 1000 * 60 * 60 * 15;
		std::string filename = "cycle_time.txt";

		CycleTester cycle_logger;
		cycle_logger.CreateStorage(filename, size);

		while (!is_stop_forced.load())
		{
			ethercat_config->GetTimer()->Sleep();

			cycle_logger.CaptureCycleBegin(ethercat_config->GetTimer()->GetCurrentTime()); /* Cycle begin */
		
			ethercat_config->PreProcessingAction();
			device->Action();
			ethercat_config->PostProcessingAction();

			cycle_logger.CaptureCycleEnd(ethercat_config->GetTimer()->GetCurrentTime()); /* Cycle end */
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
