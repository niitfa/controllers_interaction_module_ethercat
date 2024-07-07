#include "kv_filter_drive_move_task.h"

void RealKVFilterDriveMoveTask::SetTargetPosition(float position)
{
    task.SetTargetPosition(position);
    this->target_position_deg = position;
}

void RealKVFilterDriveMoveTask::SetVelocity(float velocity)
{
    task.SetTargetVelocity(velocity);
    this->target_velocity_deg_per_sec = velocity;
}

void RealKVFilterDriveMoveTask::StateRun()
{
    auto drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    task.SetUnitsRatio(drive_props.thread_pitch / drive_props.microstep_resolution);
    if(drive)
    {
        task.RunTask(this->GetContext());
    }
}