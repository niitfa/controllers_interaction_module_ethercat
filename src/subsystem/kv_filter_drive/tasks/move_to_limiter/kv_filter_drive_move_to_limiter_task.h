#ifndef KV_FILTER_DRIVE_MOVE_TO_LIMITER_H
#define KV_FILTER_DRIVE_MOVE_TO_LIMITER_H

#include "kv_filter_drive.h"

class KVFilterDriveMoveToLimiterTask : public KVFilterDriveTask,
    SubsystemStateSelector<KVFilterDriveTask, class KVFilterDriveMoveToLimiterTask, class RealKVFilterDriveMoveToLimiterTask, class EmulatedKVFilterDriveMoveToLimiterTask>
{
protected:
    KVFilterDrive::Properties drive_props;  
    int8_t mode_of_operation_out = 0;
    int32_t target_velocity_c = 0;
    float target_velocity_mm = 0; 
    int32_t actual_velocity_drive_c = 0;
    float actual_velocity_drive_mm = 0;
    float actual_velocity_wire_sensor_mm = 0;
    uint32_t frequency = 0;
public:
    void SetVelocity(float velocity);
    void SavePropertiesOf(KVFilterDrive* kv_filter_drive);
};

class RealKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{
    int task_state = 0;
public:
    RealKVFilterDriveMoveToLimiterTask();
    void StateRun() override;
};

class EmulatedKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{
public:
    void StateRun() override;
};

#endif