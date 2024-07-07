#include "emulated_gantry.h"

EmulatedGantry::EmulatedGantry(uint32_t microstep_resolution, float gear_ratio) : Gantry(microstep_resolution, gear_ratio)
{}

bool EmulatedGantry::IsEmulated()
{
    return true;
}

void EmulatedGantry::ModifyTelemetry()
{
}