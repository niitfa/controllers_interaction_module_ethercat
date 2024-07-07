#ifndef EMULATED_GANTRY_H
#define EMULATED_GANTRY_H

#include "gantry.h"

class EmulatedGantry : public Gantry
{
public:
	EmulatedGantry(uint32_t microstep_resolution, float gear_ratio);
	bool IsEmulated() override; /* always true */
	void ModifyTelemetry() override;
};

#endif