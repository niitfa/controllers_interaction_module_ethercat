#ifndef COMMON_HOMING_DRIVE_TASK_H
#define COMMON_HOMING_DRIVE_TASK_H

#include "ethercat_slave.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"

template<class TContext>
class CommonHomingTask
{
    int homing_method = 0;
public:
    void RunTask(TContext* context);
    void SetHomingMethod(int homing_method)
    {
        this->homing_method = homing_method;
    }
};

template<class TContext>
void CommonHomingTask<TContext>::RunTask(TContext* context)
{
    //EthercatSlave* drive = context->GetSubsystem()->GetDrive();
 	//int64_t statusword = drive->GetTxPDOEntry(coe_object_names::kStatusword)->LoadValue();
	//int64_t controlword = drive->GetRxPDOEntry(coe_object_names::kControlword)->LoadValue();

}


#endif