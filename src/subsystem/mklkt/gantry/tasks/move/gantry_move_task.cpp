#include "gantry_move_task.h"

void GantryMoveTask::SetTargetPosition(float position)
{
    this->target_position_deg = position;
}

void GantryMoveTask::SetVelocity(float velocity)
{
    this->target_velocity_deg_per_sec = velocity;
}