#ifndef REAL_GANTRY_H
#define REAL_GANTRY_H

#include "gantry.h"

class RealGantry : public Gantry
{
public:
	RealGantry(uint32_t microstep_resolution, float gear_ratio);
	bool IsEmulated() override; /* always false */
	void ModifyTelemetry() override;
};

#endif