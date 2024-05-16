#include "io_module_cn8033.h"
#include "ethercat_slave_names.h"

bool IOModuleCN8033::IsEmulated()
{
    return false;
}

void IOModuleCN8033::ModifyTelemetry()
{
    auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
    auto val = this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetTxPDOEntry("Ch#2")->LoadValue();
    //auto val = this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetTelemetrySDOEntry("sdo input")->LoadValue();
    std::cout << "val: " << val << "\n";
    master_telemetry->analog_input_1 = 0;

    //this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry("Ch#2")->StoreValue(1);
    //this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry("Ch#5")->StoreValue(1);
}

void IOModuleCN8033::RegisterIOModule(EthercatSlave* slave)
{
    this->io_module_slave = slave;
}

EthercatSlave* IOModuleCN8033::GetIOModule()
{
    return this->io_module_slave;
}