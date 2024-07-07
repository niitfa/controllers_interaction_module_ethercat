#ifndef GANTRY_TASK_STATE_H
#define GANTRY_TASK_STATE_H

#include "state_content_creator.h"

class GantryTaskState : public StateContentCreator<class GantryTaskContext, class GantryTaskState, class Gantry, GantryTelemetry>
{
};

#endif