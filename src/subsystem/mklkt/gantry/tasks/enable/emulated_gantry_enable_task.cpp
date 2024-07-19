#include "gantry_enable_task.h"
#include "coe_drive_state_handler.h"

using namespace coe_drive_state_handler;

EmulatedGantryEnableTask::EmulatedGantryEnableTask() : GantryEnableTask()
{
    this->delay_counter = 0;
}

void EmulatedGantryEnableTask::StateRun()
{
    delay_counter++;
    if (delay_counter == kEnablingDelayCycles)
    {
        this->GetMasterTelemetry()->pds_drive_state = kStateOperationEnabled;
        this->GetMasterTelemetry()->is_drive_enabled = true;
        GantryTaskState::GetContext()->TransitToNext();
    }
}