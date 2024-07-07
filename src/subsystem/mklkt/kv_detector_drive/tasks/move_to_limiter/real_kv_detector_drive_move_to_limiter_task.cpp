#include "kv_detector_drive_move_to_limiter_task.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

using namespace coe_object_names;
using namespace coe_drive_state_handler;

RealKVDetectorDriveMoveToLimiterTask::RealKVDetectorDriveMoveToLimiterTask()
{}

void RealKVDetectorDriveMoveToLimiterTask::StateRun()
{   
    this->drive_props = this->GetContext()->GetSubsystem()->GetProperties();
    auto drive = this->GetContext()->GetSubsystem()->GetDrive();
    task.SetUnitsRatio(drive_props.thread_pitch / drive_props.microstep_resolution);
    if(drive)
    {
        task.RunTask(this->GetContext());
    }
}

void RealKVDetectorDriveMoveToLimiterTask::SetVelocity(float velocity)
{
    this->target_velocity_mm = velocity;
    task.SetTargetVelocity(velocity);
}