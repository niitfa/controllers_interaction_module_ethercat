#include "emulated_kv_detector_drive.h"

EmulatedKVDetectorDrive::EmulatedKVDetectorDrive(uint32_t microstep_resolution, float thread_pitch) : KVDetectorDrive(microstep_resolution, thread_pitch)
{}

bool EmulatedKVDetectorDrive::IsEmulated()
{
    return true;
}

void EmulatedKVDetectorDrive::ModifyTelemetry()
{

}