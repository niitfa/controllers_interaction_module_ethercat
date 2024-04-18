#ifndef GANTRY_H
#define GANTRY_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "gantry_telemetry.h"
#include "gantry_task_state.h"
#include "gantry_task_context.h"

class Gantry : public SubsystemContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{
};

#endif

