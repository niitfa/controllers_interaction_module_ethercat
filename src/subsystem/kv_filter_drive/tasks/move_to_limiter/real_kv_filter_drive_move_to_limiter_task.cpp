#include "kv_filter_drive_move_to_limiter_task.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

using namespace coe_object_names;
using namespace coe_drive_state_handler;

RealKVFilterDriveMoveToLimiterTask::RealKVFilterDriveMoveToLimiterTask()
{
    this->task_state = 0;
}

void RealKVFilterDriveMoveToLimiterTask::StateRun()
{
    this->frequency = this->GetContext()->GetSubsystem()->GetEthercatConfig()->GetTimer()->GetFrequency();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    this->drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    
    if(drive)
    {
        actual_velocity_drive_c = drive->GetTxPDOEntry(kActualVelocity)->LoadValue();
        actual_velocity_drive_mm = actual_velocity_drive_c * drive_props.thread_pitch / drive_props.microstep_resolution;
        actual_velocity_wire_sensor_mm = this->GetContext()->GetTelemetryExchanger()->GetMasterTelemetry()->wire_sensor_velocity_mm;
        target_velocity_c = (int32_t)(target_velocity_mm * drive_props.microstep_resolution / drive_props.thread_pitch);
        std::cout << "RealKVFilterDriveMoveToLimiterTask::StateRun(): wire: " << actual_velocity_wire_sensor_mm << "\tdrive: " <<  actual_velocity_drive_mm << std::endl;

        switch (task_state)
        {
            /* Enabling PV mode */
            case 0: 

            drive->GetRxPDOEntry(kProfileVelocity)->StoreValue(target_velocity_c);
            drive->GetRxPDOEntry(kModeOfOperation)->StoreValue(kModeProfileVelocity);
            mode_of_operation_out = drive->GetTxPDOEntry(kModeOfOperationOut)->LoadValue();
             
            if(mode_of_operation_out == kModeProfileVelocity)
            {
                task_state++; 
            }  
            break;
            case 1:
            if(abs(actual_velocity_drive_c - target_velocity_c) < 0.10 * abs(target_velocity_c))
            {
               task_state++;
            }
            //drive->GetRxPDOEntry(kModeOfOperation)->StoreValue(kModeProfilePosition); // 
            //task_state++;
            // 2 движение с постоянной скоростью до коллизии
            break;
            case 2:
            if(abs(actual_velocity_wire_sensor_mm) == 0)
            {
                drive->GetRxPDOEntry(kModeOfOperation)->StoreValue(kModeProfilePosition);
            }
            break;
        }
    }


    // 1 разгон
    // 2 движение с постоянной скоростью до коллизии
    // 3 выход из pv
}