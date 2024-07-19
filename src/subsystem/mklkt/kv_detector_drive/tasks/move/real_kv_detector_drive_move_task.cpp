#include "kv_detector_drive_move_task.h"

void RealKVDetectorDriveMoveTask::SetTargetPosition(float position)
{
    task.SetTargetPosition(position);
    this->target_position_mm = position;
}

void RealKVDetectorDriveMoveTask::SetVelocity(float velocity)
{
    task.SetTargetVelocity(velocity);
    this->target_velocity_mm_per_sec = velocity;
}

void RealKVDetectorDriveMoveTask::StateRun()
{
    auto drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    task.SetUnitsRatio(drive_props.thread_pitch / drive_props.microstep_resolution);
    if(drive)
    {
        task.RunTask(this->GetContext());
    }
}