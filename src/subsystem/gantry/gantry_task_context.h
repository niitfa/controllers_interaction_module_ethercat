#ifndef GANTRY_TASK_CONTEXT_H
#define GANTRY_TASK_CONTEXT_H

#include "context_content_creator.h"

class GantryTaskContext : public ContextContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{
};

#endif