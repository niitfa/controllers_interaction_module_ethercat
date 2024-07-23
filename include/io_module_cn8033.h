#ifndef IO_MODULE_CN8033_H
#define IO_MODULE_CN8033_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "io_module_cn8033_telemetry.h"
#include "io_module_cn8033_task_state.h"
#include "io_module_cn8033_task_context.h"

#include "ethercat_slave.h"

class IOModuleCN8033 : public SubsystemContentCreator<IOModuleCN8033TaskContext, IOModuleCN8033TaskState, IOModuleCN8033, IOModuleCN8033Telemetry>
{
    EthercatSlave* io_module_slave = nullptr;
public:
    bool IsEmulated() override;
    void ModifyTelemetry() override;
    void RegisterIOModule(EthercatSlave* slave);
    EthercatSlave* GetIOModule();
};


#endif