#include "kv_filter_drive_move_to_limiter_task.h"

void KVFilterDriveMoveToLimiterTask::SetVelocity(float velocity)
{
    this->target_velocity_mm = velocity;
}

void KVFilterDriveMoveToLimiterTask::SavePropertiesOf(KVFilterDrive* kv_filter_drive)
{
    this->drive_props = kv_filter_drive->GetProperties();
}