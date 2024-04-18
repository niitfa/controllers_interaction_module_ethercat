#ifndef LONELY_DRIVE_TELEMETRY_H
#define LONELY_DRIVE_TELEMETRY_H

#include <stdint.h>

struct LonelyDriveTelemetry
{
	int32_t pds_state = 0;
	int32_t drive_position_count = 0;
	int32_t drive_velocity_count_per_sec = 0;	
};


#endif