#include "io_module_cn8033.h"

bool IOModuleCN8033::IsEmulated()
{
    return false;
}

void IOModuleCN8033::ModifyTelemetry()
{
    auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
    master_telemetry->analog_input_1 = 0;
}

void IOModuleCN8033::RegisterIOModule(EthercatSlave* slave)
{
    this->io_module_slave = slave;
}

EthercatSlave* IOModuleCN8033::GetIOModule()
{
    return this->io_module_slave;
}