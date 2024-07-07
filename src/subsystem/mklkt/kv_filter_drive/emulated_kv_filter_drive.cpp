#include "emulated_kv_filter_drive.h"

EmulatedKVFilterDrive::EmulatedKVFilterDrive(uint32_t microstep_resolution, float thread_pitch) : KVFilterDrive(microstep_resolution, thread_pitch)
{}

bool EmulatedKVFilterDrive::IsEmulated()
{
    return true;
}

void EmulatedKVFilterDrive::ModifyTelemetry()
{

}