#ifndef ETHERCAT_THREAD_BUILDER_H
#define ETHERCAT_THREAD_BUILDER_H

#include "ethercat_thread_manager.h"
#include "io_module_cn8033.h"
#include "unspecified_device.h"

class EthercatThreadBuilder
{
    EthercatThreadBuilder() = delete;
public:
    struct IOModuleThreadContent
    {
        EthercatThreadManager* thread;
        UnspecifiedDevice* device;
        IOModuleCN8033* io_module;
    };
    
    static IOModuleThreadContent BuildThread_IOModule(int master_index);
};

#endif