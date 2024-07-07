#ifndef KV_FILTER_DRIVE_MOVE_TO_LIMITER_H
#define KV_FILTER_DRIVE_MOVE_TO_LIMITER_H

#include "kv_filter_drive.h"
#include "common_move_to_limiter_drive_task.h"

class KVFilterDriveMoveToLimiterTask : public KVFilterDriveTask,
    SubsystemStateSelector<KVFilterDriveTask, class KVFilterDriveMoveToLimiterTask, class RealKVFilterDriveMoveToLimiterTask, class EmulatedKVFilterDriveMoveToLimiterTask>
{
protected:
    KVFilterDrive::Properties drive_props;  
    float target_velocity_mm = 0; 
public:
    virtual void SetVelocity(float velocity);
};

class RealKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{
    CommonMoveToLimiterDriveTask<KVFilterDriveContext> task;
public:
    RealKVFilterDriveMoveToLimiterTask();
    void StateRun() override;
    void SetVelocity(float velocity) override;
};

class EmulatedKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{
public:
    void StateRun() override;
};

#endif