#ifndef GANTRY_TELEMETRY_H
#define GANTRY_TELEMETRY_H

#include <stdint.h>

struct GantryTelemetry
{
	int32_t gantry_position_count = 0;
	int32_t gantry_velocity_count_per_sec = 0;	
};

#endif