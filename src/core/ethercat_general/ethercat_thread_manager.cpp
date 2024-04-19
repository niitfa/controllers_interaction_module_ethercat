#include "ethercat_thread_manager.h"
#include "stopwatch.h"

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
		Stopwatch sw; /* Для монитрина длительности цикла при отладке */
		auto ethercat_config = device->GetEthercatConfig();
		ethercat_config->Initialize();
		is_initialized.store(true);
		while (!is_stop_forced.load())
		{
			ethercat_config->GetTimer()->Sleep();
			sw.Reset();
			ethercat_config->PreProcessingAction();
			device->Action();
			ethercat_config->PostProcessingAction();
			sw.Update();
			//std::cout << "Thread manager cycle dur: " << sw.Microseconds() << std::endl;
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
