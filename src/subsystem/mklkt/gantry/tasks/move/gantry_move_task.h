#ifndef GANTRY_MOVE_TASK_H
#define GANTRY_MOVE_TASK_H

#include "gantry.h"
#include "common_move_drive_task.h"

class GantryMoveTask : public GantryTaskState,
    public SubsystemStateSelector<Gantry, class GantryMoveTask, class RealGantryMoveTask, class EmlatedGantryMoveTask>
{
protected:
    float target_position_deg = 0;
    float target_velocity_deg_per_sec = 0;
public:
    virtual void SetTargetPosition(float position);
    virtual void SetVelocity(float velocity);
};

class EmulatedGantryMoveTask : public GantryMoveTask
{
public:
    void StateRun() override;
};

class RealGantryMoveTask : public GantryMoveTask
{
    CommonMoveDriveTask<GantryTaskContext> task;
public:
    void StateRun() override;
    void SetTargetPosition(float position) override;
    void SetVelocity(float velocity) override;
};

#endif