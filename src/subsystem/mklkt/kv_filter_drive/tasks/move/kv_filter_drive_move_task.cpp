#include "kv_filter_drive_move_task.h"

void KVFilterDriveMoveTask::SetTargetPosition(float position)
{
    this->target_position_deg = position;
}

void KVFilterDriveMoveTask::SetVelocity(float velocity)
{
    this->target_velocity_deg_per_sec = velocity;
}