#ifndef ETHERCAT_THREAD_BUILDER_H
#define ETHERCAT_THREAD_BUILDER_H

#include "ethercat_thread_manager.h"
#include "unspecified_device.h"

#include "io_module_cn8033.h"
#include "real_kv_filter_drive.h"

#include "real_lonely_drive.h"

class EthercatThreadBuilder
{
    EthercatThreadBuilder() = delete;
public:
    /*
        Slave 0 - IO Module ODOT CN-8033 + CT-3168 + CT-632F 
    */    
    struct IOModuleThreadContent
    {
        EthercatThreadManager* thread = nullptr;
        UnspecifiedDevice* device = nullptr;
        IOModuleCN8033* io_module = nullptr;
    };

    static IOModuleThreadContent BuildThread_IOModule(int master_index);

    /*
        Slave 0 - Leadshine DM3C-EC556 CoE Drive
    */
    struct DriveThreadContent
    {
        EthercatThreadManager* thread = nullptr;
        UnspecifiedDevice* device = nullptr;
        RealLonelyDrive* drive = nullptr;
    };
    static DriveThreadContent BuildThread_Drive(int master_index);


    /*
        Slave 0 - Leadshine DM3C-EC556 CoE Drive    
        Slave 1 - IO Module ODOT CN-8033 + CT-3168 + CT-632F 
    */
    struct Drive_IOModule_ThreadContent
    {
        EthercatThreadManager* thread = nullptr;
        UnspecifiedDevice* device = nullptr;
        RealKVFilterDrive* kv_drive = nullptr;
        
    };

   static Drive_IOModule_ThreadContent BuildThread_Drive_IOModule(int master_index);


    
};

#endif