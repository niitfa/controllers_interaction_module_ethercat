#ifndef KV_FILTER_DRIVE_TELEMETRY_H
#define KV_FILTER_DRIVE_TELEMETRY_H

#include <stdint.h>

struct KVFilterDriveTelemetry
{
    int32_t position_count = 0;
    float wire_sensor_velocity_mm = 0;
};

#endif