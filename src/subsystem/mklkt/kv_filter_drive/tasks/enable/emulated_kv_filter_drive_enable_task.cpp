#include "kv_filter_drive_enable_task.h"
#include "coe_drive_state_handler.h"

using namespace coe_drive_state_handler;

EmulatedKVFilterDriveEnableTask::EmulatedKVFilterDriveEnableTask()
{
    this->delay_counter = 0;
}

void EmulatedKVFilterDriveEnableTask::StateRun()
{
    delay_counter++;
    if (delay_counter == kEnablingDelayCycles)
    {
        this->GetMasterTelemetry()->pds_drive_state = kStateOperationEnabled;
        this->GetMasterTelemetry()->is_drive_enabled = true;
        KVFilterDriveTask::GetContext()->TransitToNext();
    }
}