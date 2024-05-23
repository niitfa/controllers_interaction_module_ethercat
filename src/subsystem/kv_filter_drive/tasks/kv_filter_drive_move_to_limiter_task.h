#ifndef KV_FILTER_DRIVE_MOVE_TO_LIMITER_H
#define KV_FILTER_DRIVE_MOVE_TO_LIMITER_H

#include "kv_filter_drive.h"

class KVFilterDriveMoveToLimiterTask : public KVFilterDriveTask,
    SubsystemStateSelector<KVFilterDriveTask, class KVFilterDriveMoveToLimiterTask, class RealKVFilterDriveMoveToLimiterTask, class EmulatedKVFilterDriveMoveToLimiterTask>
{
protected:
    bool direction = 0;
    float velocity_mm_per_sec = 0;
public:
    void SetDirection(bool direction);

};

class RealKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{

};

class EmulatedKVFilterDriveMoveToLimiterTask : public KVFilterDriveMoveToLimiterTask
{

};

#endif