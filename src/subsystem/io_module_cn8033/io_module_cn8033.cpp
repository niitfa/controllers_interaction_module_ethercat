#include "io_module_cn8033.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

bool IOModuleCN8033::IsEmulated()
{
    return false;
}

void IOModuleCN8033::ModifyTelemetry()
{
    auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
    auto val_0 = this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetTxPDOEntry(kCT3168_AI0)->LoadValue();
    auto val_1 = this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetTxPDOEntry(kCT3168_AI1)->LoadValue();
    //auto val = this->GetEthercatConfig()->GetSlaves()->GetSlave(ethercat_slave_names::kIOModuleName)->GetTelemetrySDOEntry("sdo input")->LoadValue();
    std::cout << "val_count_enc0: " << val_0 << "\t"; //<< "\tval_volt: " << (float)val * 10 / 27648 << "\tval_mm: "<< (float)val * 10 / 27648 * 1000 / 3.5 / 24 << "\n";
    std::cout << "val_count_enc1: " << val_1 << std::endl;
    master_telemetry->analog_input_1 = 0;

    // DEBUG
    this->GetEthercatConfig()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry(kCT632F_DO1)->StoreValue(1);
    this->GetEthercatConfig()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry(kCT632F_DO3)->StoreValue(1);
    this->GetEthercatConfig()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry(kCT632F_DO5)->StoreValue(1);
    this->GetEthercatConfig()->GetSlave(ethercat_slave_names::kIOModuleName)->GetRxPDOEntry(kCT632F_DO7)->StoreValue(1);

}

void IOModuleCN8033::RegisterIOModule(EthercatSlave* slave)
{
    this->io_module_slave = slave;
}

EthercatSlave* IOModuleCN8033::GetIOModule()
{
    return this->io_module_slave;
}