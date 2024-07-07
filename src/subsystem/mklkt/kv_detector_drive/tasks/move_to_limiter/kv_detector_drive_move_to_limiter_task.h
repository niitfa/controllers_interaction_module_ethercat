#ifndef KV_DETECTOR_DRIVE_MOVE_TO_LIMITER_H
#define KV_DETECTOR_DRIVE_MOVE_TO_LIMITER_H

#include "kv_detector_drive.h"
#include "common_move_to_limiter_drive_task.h"

class KVDetectorDriveMoveToLimiterTask : public KVDetectorDriveTask,
    SubsystemStateSelector<
    KVDetectorDriveTask,
    class KVDetectorDriveMoveToLimiterTask, 
    class RealKVDetectorDriveMoveToLimiterTask, 
    class EmulatedKVDetectorDriveMoveToLimiterTask>
{
protected:
    KVDetectorDrive::Properties drive_props;  
    float target_velocity_mm = 0; 
public:
    virtual void SetVelocity(float velocity);
};

class RealKVDetectorDriveMoveToLimiterTask : public KVDetectorDriveMoveToLimiterTask
{
    CommonMoveToLimiterDriveTask<KVDetectorDriveContext> task;
public:
    RealKVDetectorDriveMoveToLimiterTask();
    void StateRun() override;
    void SetVelocity(float velocity) override;
};

class EmulatedKVDetectorDriveMoveToLimiterTask : public KVDetectorDriveMoveToLimiterTask
{
public:
    void StateRun() override;
};

#endif