#include "mklkt_model.h"

void MKLKTModel::RegisterGantry(Gantry* g)
{
    DeviceModel::RegisterSubsystem(g, (Subsystem**)&gantry);
}

void MKLKTModel::RegisterKVDetectorDrive(KVDetectorDrive* kv_d)
{
    DeviceModel::RegisterSubsystem(kv_d, (Subsystem**)&kv_detector_drive);
}

void MKLKTModel::RegisterKVFilterDrive(KVFilterDrive* kv_f)
{
    DeviceModel::RegisterSubsystem(kv_f, (Subsystem**)&kv_filter_drive);
}

Gantry* MKLKTModel::GetGantry() const
{
    return this->gantry;
}

KVDetectorDrive* MKLKTModel::GetKVDetectorDrive() const
{
    return this->kv_detector_drive;
}

KVFilterDrive* MKLKTModel::GetKVFilterDrive() const
{
    return this->kv_filter_drive;
}