#ifndef GANTRY_TELEMETRY_H
#define GANTRY_TELEMETRY_H

#include <stdint.h>
#include "coe_drive_state_handler.h"

struct GantryTelemetry
{
	coe_drive_state_handler::PowerDriveSystemState pds_drive_state = coe_drive_state_handler::kStateUndefined;
	bool is_drive_enabled = false;
    int32_t drive_position_pulse = 0;    
    int32_t drive_velocity_pulse_per_sec = 0;
    float drive_position_deg = 0;
    float drive_velocity_deg_per_sec = 0; 
};

#endif