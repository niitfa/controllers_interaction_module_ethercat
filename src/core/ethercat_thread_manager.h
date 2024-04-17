#ifndef ETHERCATTHREADMANAGER_H
#define ETHERCATTHREADMANAGER_H

#include <thread>
#include <atomic>
#include "device_model.h"
#include "ethercat_configuration.h"

class EthercatThreadManager
{
	DeviceModel* device = nullptr;
	std::atomic<bool> is_launched; // для контроля наличия активного потока
	std::atomic<bool> is_initialized;  // для контроля блокировки в главном потоке в процессе инициализации
	std::atomic<bool> is_stop_forced; // для размещения в условии while и остановки при вызове StopThread()
public:
	EthercatThreadManager();
	~EthercatThreadManager();
	void RegisterDevice(DeviceModel*);
	void StartThread();
	void StopThread();
private:
	void Handler();
	void WaitForInit();
};

#endif
