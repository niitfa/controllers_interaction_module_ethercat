#ifndef KV_FILTER_DRIVE_TELEMETRY_H
#define KV_FILTER_DRIVE_TELEMETRY_H

#include <stdint.h>

struct KVFilterDriveTelemetry
{
    int32_t drive_position_pulse = 0;    
    int32_t drive_velocity_pulse_per_sec = 0;
    int32_t wire_sensor_position_pulse = 0; 
    int32_t wire_sensor_velocity_pulse_per_sec = 0;
    float drive_position_mm = 0;
    float drive_velocity_mm_per_sec = 0;
    float wire_sensor_position_mm = 0;
    float wire_sensor_velocity_mm_per_sec = 0;    
};

#endif