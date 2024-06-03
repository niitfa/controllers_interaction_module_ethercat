#include "kv_detector_drive_move_to_limiter_task.h"

void KVDetectorDriveMoveToLimiterTask::SetVelocity(float velocity)
{
    this->target_velocity_mm = velocity;
}