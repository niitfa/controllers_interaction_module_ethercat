#ifndef KV_DETECTOR_DRIVE_MOVE_TASK_H
#define KV_DETECTOR_DRIVE_MOVE_TASK_H

#include "kv_detector_drive.h"
#include "common_move_drive_task.h"

class KVDetectorDriveMoveTask : public KVDetectorDriveTask,
    public SubsystemStateSelector<KVDetectorDrive, class KVDetectorDriveMoveTask, class RealKVDetectorDriveMoveTask, class EmlatedKVDetectorDriveMoveTask>
{
protected:
    float target_position_deg = 0;
    float target_velocity_deg_per_sec = 0;
public:
    virtual void SetTargetPosition(float position);
    virtual void SetVelocity(float velocity);
};

class EmulatedKVDetectorDriveMoveTask : public KVDetectorDriveMoveTask
{
public:
    void StateRun() override;
};

class RealKVDetectorDriveMoveTask : public KVDetectorDriveMoveTask
{
    CommonMoveDriveTask<KVDetectorDriveContext> task;
public:
    void StateRun() override;
    void SetTargetPosition(float position) override;
    void SetVelocity(float velocity) override;
};

#endif