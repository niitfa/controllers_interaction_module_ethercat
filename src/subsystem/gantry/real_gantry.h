#ifndef REAL_GANTRY_H
#define REAL_GANTRY_H

#include "gantry.h"

class RealGantry : public Gantry
{
public:
	bool IsEmulated() override; /* always false */
	void ModifyTelemetry() override;
};

#endif