/**
 * @brief Main user object. Used for starting and stopping ethercat thread.
 * @details Configuration example:
 * @code
 * #include "ethercat_thread_manager.h"
 * #inclide "unspecified_device.h"
 * 
 * void ConfigureEthercatThread()
 * {
 * 		UnspecifiedDevice* device;
 * 
 * 		// Class UnspecifiedDevice is derived from DeviceModel.
 * 		// Let's see device was previously configured.
 * 		// See UnspecifiedDevice configuration example in class definition.
 * 
 * 		EthercatThreadManager* ethercat_thread = new EthercatThreadManager();
 * 		ethercat_thread->RegisterDevice(device);
 * 		
 * 		// Launch thread
 * 		ethercat_thread->StartThread();
 * 		
 * 		// Some thread opeations...
 * 
 * 		// Break thread
 * 		ethercat_thread->StopThread();
 * 		delete ethercat_thread;	
 * }
 * @endcode
*/

#ifndef ETHERCAT_THREAD_MANAGER_H
#define ETHERCAT_THREAD_MANAGER_H

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
	/**
	 * @brief Passes previously configured device, which contains
	 * subsystems and ethercat network properties.
	 * @param[in] device Pointer to device.
	*/
	void RegisterDevice(DeviceModel* device);
	/**
	 * @brief Starts thread.
	*/
	void StartThread();
	/**
	 * @brief Stops thread.
	*/
	void StopThread();
private:
	/**
	 * @brief Main ethercat thread method. 
	*/
	void Handler();
	/**
	 * @brief Blocks user thread before ethercat thread is initialized.
	*/
	void WaitForInit();
};

#endif
