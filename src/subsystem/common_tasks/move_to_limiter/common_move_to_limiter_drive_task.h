#ifndef COMMON_MOVE_TO_LIMITER_DRIVE_TASK_H
#define COMMON_MOVE_TO_LIMITER_DRIVE_TASK_H

#include "ethercat_slave.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

template<class TContext>
class CommonMoveToLimiterDriveTask
{
    int task_state {0};
    float target_velocity_user_units {0};
    float units_per_count_ratio {1};
public:
    CommonMoveToLimiterDriveTask();
    void RunTask(TContext* context);
    void SetTargetVelocity(float velocity);
    void SetUnitsRatio(float ratio);
};

template<class TContext>
CommonMoveToLimiterDriveTask<TContext>::CommonMoveToLimiterDriveTask()
     : task_state {0}, target_velocity_user_units {0}, units_per_count_ratio {1}
{}

template<class TContext>
void CommonMoveToLimiterDriveTask<TContext>::RunTask(TContext* context)
{
    EthercatSlave* drive = context->GetSubsystem()->GetDrive();
    uint32_t frequency = context->GetSubsystem()->GetEthercatConfig()->GetTimer()->GetFrequency();
    int32_t actual_velocity_drive_c = drive->GetTxPDOEntry(coe_object_names::kActualVelocity)->LoadValue();
    float actual_velocity_drive_mm = actual_velocity_drive_c * units_per_count_ratio;
    float actual_velocity_wire_sensor_mm = context->GetTelemetryExchanger()->GetMasterTelemetry()->wire_sensor_velocity_mm_per_sec;
    int32_t target_velocity_c = (int32_t)(target_velocity_user_units  / units_per_count_ratio);
    int8_t mode_of_operation_out = drive->GetTxPDOEntry(coe_object_names::kModeOfOperationOut)->LoadValue();
    switch (task_state)
    {
        /* Enabling PV mode */
        case 0: 
        drive->GetRxPDOEntry(coe_object_names::kProfileVelocity)->StoreValue(target_velocity_c);
        drive->GetRxPDOEntry(coe_object_names::kModeOfOperation)->StoreValue(coe_drive_state_handler::ModeOfOperation::kModeProfileVelocity);
             
        if(mode_of_operation_out == coe_drive_state_handler::ModeOfOperation::kModeProfileVelocity)
        {
            task_state++; 
        }  
        break;
        case 1:
        //if(abs(actual_velocity_drive_c - target_velocity_c) < 0.10 * abs(target_velocity_c))
        //{
        //   task_state++;
        //}
        // 2 движение с постоянной скоростью до коллизии
        break;
        case 2:
        if(abs(actual_velocity_wire_sensor_mm) == 0)
        {
            drive->GetRxPDOEntry(coe_object_names::kModeOfOperation)->StoreValue(coe_drive_state_handler::ModeOfOperation::kModeProfilePosition);
            context->TransitToNext();
        }
        break;
    }
}

template<class TContext>
void CommonMoveToLimiterDriveTask<TContext>::SetTargetVelocity(float velocity)
{
    this->target_velocity_user_units = velocity;
}

template<class TContext>
void CommonMoveToLimiterDriveTask<TContext>::SetUnitsRatio(float ratio)
{
    this->units_per_count_ratio = ratio;
}

#endif