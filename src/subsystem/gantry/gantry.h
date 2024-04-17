#ifndef GANTRY_H
#define GANTRY_H

#include "subsystem.h"
#include "subsystem_state_selector.h"

/* Это структура телеметрии, является полем класса Gantry */
struct GantryTelemetry
{
	int32_t gantry_position_count = 0;
	int32_t gantry_velocity_count_per_sec = 0;	
};

class Gantry;
class GantryTaskContext;
class GantryTaskState;

class GantryTaskState 	: public StateContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{};
class GantryTaskContext : public ContextContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{};
class Gantry 			: public SubsystemContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{
	/* int32_t position_offset */
};

class RealGantry : public Gantry
{
public:
	bool IsEmulated() override { return false; }
	void ModifyTelemetry() override;
};

class EmulatedGantry : public Gantry
{
public:
	bool IsEmulated() override { return true; }
	void ModifyTelemetry() override;
};

#endif

