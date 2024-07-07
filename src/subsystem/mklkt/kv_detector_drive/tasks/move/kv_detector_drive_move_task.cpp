#include "kv_detector_drive_move_task.h"

void KVDetectorDriveMoveTask::SetTargetPosition(float position)
{
    this->target_position_deg = position;
}

void KVDetectorDriveMoveTask::SetVelocity(float velocity)
{
    this->target_velocity_deg_per_sec = velocity;
}