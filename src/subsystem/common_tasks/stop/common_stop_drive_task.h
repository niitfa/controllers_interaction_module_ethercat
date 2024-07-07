#ifndef COMMON_STOP_DRIVE_TASK_H
#define COMMON_STOP_DRIVE_TASK_H

#include "ethercat_slave.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

template<class TContext>
class CommonStopDriveTask
{
    int task_state {0};
public:
    CommonStopDriveTask();
    void RunTask(TContext* context);
};

template<class TContext>
CommonStopDriveTask<TContext>::CommonStopDriveTask() : task_state {0}
{}

template<class TContext>
void CommonStopDriveTask<TContext>::RunTask(TContext* context)
{
    EthercatSlave* drive = context->GetSubsystem()->GetDrive();
    int32_t target_velocity_c = 0;
    int32_t actual_velocity_drive_c = drive->GetTxPDOEntry(coe_object_names::kActualVelocity)->LoadValue();
    int64_t mode_of_operation_out = drive->GetTxPDOEntry(coe_object_names::kModeOfOperationOut)->LoadValue();

    switch (task_state)
    {
        case 0: 
        drive->GetRxPDOEntry(coe_object_names::kProfileVelocity)->StoreValue(target_velocity_c);
        drive->GetRxPDOEntry(coe_object_names::kModeOfOperation)->StoreValue(coe_drive_state_handler::ModeOfOperation::kModeProfileVelocity);
             
        if(mode_of_operation_out == coe_drive_state_handler::ModeOfOperation::kModeProfileVelocity)
        {
            task_state++; 
        }  
        break;
        case 1:
        if(abs(actual_velocity_drive_c) == 0)
        {
            context->TransitToNext();
        }
        break;
    }
}

#endif