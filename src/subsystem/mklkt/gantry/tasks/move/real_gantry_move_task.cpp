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
    constexpr float kDegreesPerRotation = 360;
    auto drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    task.SetUnitsRatio(kDegreesPerRotation / drive_props.microstep_resolution / drive_props.gear_ratio);

    if(drive)
    {
        task.RunTask(this->GetContext());
    }
}