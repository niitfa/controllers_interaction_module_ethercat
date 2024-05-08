#include "ethercat_thread_builder.h"
#include "ethercat_thread_manager.h"
#include "ethercat_slave_builder.h"
#include "ethercat_slaves_container.h"
#include "simple_timer.h"
#include "io_module_cn8033.h"

EthercatThreadBuilder::IOModuleThreadContent EthercatThreadBuilder::BuildThread_IOModule(int master_index)
{
    uint32_t frequency_hz = 1000;

    EthercatMaster* ethercat_master = new EthercatMaster();
	ethercat_master->SetMasterIndex(master_index);

    EthercatSlavesContainer* ethercat_slaves = new EthercatSlavesContainer();
    EthercatSlave* io_module_cn_8033 = EthercatSlaveBuilder::BuildIOModule(0, 0);
    ethercat_slaves->RegisterSlave(io_module_cn_8033);

    SimpleTimer* timer = new SimpleTimer();
    timer->SetFrequency(frequency_hz);

    EthercatConfiguration* ethercat_config = new EthercatConfiguration();
    ethercat_config->RegisterMaster(ethercat_master);
	ethercat_config->RegisterSlavesContainer(ethercat_slaves);
	ethercat_config->RegisterTimer(timer);

    IOModuleCN8033* io_module = new IOModuleCN8033();
    io_module->RegisterIOModule(io_module_cn_8033);
    
    UnspecifiedDevice* device = new UnspecifiedDevice();
    device->RegisterSubsystem(io_module);
    device->RegisterEthercatConfig(ethercat_config);

    EthercatThreadManager* thread = new EthercatThreadManager(); 
    thread->RegisterDevice(device);
    thread->SetCPUs({13});   


    IOModuleThreadContent thread_content;
    thread_content.thread = thread;   
    thread_content.device = device;
    thread_content.io_module = io_module;
    
    return thread_content;

}