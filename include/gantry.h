#ifndef GANTRY_H
#define GANTRY_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "gantry_telemetry.h"
#include "gantry_task_state.h"
#include "gantry_task_context.h"

class Gantry : public SubsystemContentCreator<GantryTaskContext, GantryTaskState, Gantry, GantryTelemetry>
{
    struct Properties
    {
        uint32_t microstep_resolution = 0;
        float gear_ratio = 0;
    };
protected:
    Properties props;
    EthercatSlave* drive = nullptr;
public:
    Gantry() = delete;
    Gantry(uint32_t microstep_resolution, float gear_ratio);
    ~Gantry() = default;
    Properties GetProperties();
    void RegisterDrive(EthercatSlave* drive);
    EthercatSlave* GetDrive();
};

#endif

