#ifndef EMULATED_GANTRY_H
#define EMULATED_GANTRY_H

#include "gantry.h"

class EmulatedGantry : public Gantry
{
public:
	bool IsEmulated() override; /* always true */
	void ModifyTelemetry() override;
};

#endif