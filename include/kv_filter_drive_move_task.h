#ifndef KV_FILTER_DRIVE_MOVE_TASK_H
#define KV_FILTER_DRIVE_MOVE_TASK_H

#include "kv_filter_drive.h"
#include "common_move_drive_task.h"

class KVFilterDriveMoveTask : public KVFilterDriveTask,
    public SubsystemStateSelector<KVFilterDrive, class KVFilterDriveMoveTask, class RealKVFilterDriveMoveTask, class EmulatedKVFilterDriveMoveTask>
{
protected:
    float target_position_mm = 0;
    float target_velocity_mm_per_sec = 0;
public:
    virtual void SetTargetPosition(float position);
    virtual void SetVelocity(float velocity);
};

class EmulatedKVFilterDriveMoveTask : public KVFilterDriveMoveTask
{
public:
    void StateRun() override;
};

class RealKVFilterDriveMoveTask : public KVFilterDriveMoveTask
{
    CommonMoveDriveTask<KVFilterDriveContext> task;
public:
    void StateRun() override;
    void SetTargetPosition(float position) override;
    void SetVelocity(float velocity) override;
};

#endif