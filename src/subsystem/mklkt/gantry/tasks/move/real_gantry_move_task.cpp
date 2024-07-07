#include "gantry_move_task.h"

void RealGantryMoveTask::SetTargetPosition(float position)
{
    task.SetTargetPosition(position);
    this->target_position_deg = position;
}

void RealGantryMoveTask::SetVelocity(float velocity)
{
    task.SetTargetVelocity(velocity);
    this->target_velocity_deg_per_sec = velocity;
}

void RealGantryMoveTask::StateRun()
{
    auto drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    task.SetUnitsRatio(drive_props.gear_ratio / drive_props.microstep_resolution);
    if(drive)
    {
        task.RunTask(this->GetContext());
    }
}