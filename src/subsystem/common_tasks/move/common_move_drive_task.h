#ifndef COMMON_MOVE_DRIVE_TASK_H
#define COMMON_MOVE_DRIVE_TASK_H

#include "ethercat_slave.h"
#include "coe_drive_state_handler.h"
#include "coe_object_names.h"
#include "word_bit.h"

template<class TContext>
class CommonMoveDriveTask
{
    int task_state {0};
    float target_velocity_user_units {0};
    float target_position_user_units {0};
    float units_per_count_ratio {1};
public:
    CommonMoveDriveTask();

    void SetTargetVelocity(float velocity);
    void SetTargetPosition(float position);
    void SetUnitsRatio(float ratio);

    void RunTask(TContext* context);

};

template<class TContext>
CommonMoveDriveTask<TContext>::CommonMoveDriveTask()
     : task_state {0}, target_velocity_user_units {0}, units_per_count_ratio {1}
{} 

template<class TContext>
void CommonMoveDriveTask<TContext>::SetTargetVelocity(float velocity)
{
    this->target_velocity_user_units = velocity;
}

template<class TContext>
void CommonMoveDriveTask<TContext>::SetTargetPosition(float position)
{
    this->target_position_user_units = position;
}

template<class TContext>
void CommonMoveDriveTask<TContext>::SetUnitsRatio(float ratio)
{
    this->units_per_count_ratio = ratio;
}

template<class TContext>
void CommonMoveDriveTask<TContext>::RunTask(TContext* context)
{
    EthercatSlave* drive = context->GetSubsystem()->GetDrive();

    int64_t controlword = drive->GetRxPDOEntry(coe_object_names::kControlword)->LoadValue();
    int64_t mode_of_operation_out = drive->GetTxPDOEntry(coe_object_names::kModeOfOperationOut)->LoadValue();
    int64_t actual_position_c = drive->GetTxPDOEntry(coe_object_names::kActualPosition)->LoadValue();
    
    int32_t target_position_c = (int32_t)(this->target_position_user_units  / this->units_per_count_ratio);
    int32_t target_velocity_c = (int32_t)(this->target_velocity_user_units  / this->units_per_count_ratio);

	//std::cout << "CommonMoveDriveTask::RunTask(): pos_v: " << this->target_position_user_units << std::endl;
	//std::cout << "CommonMoveDriveTask::RunTask(): pos_c: " << target_position_c << std::endl;

    switch(this->task_state)
	{
		case 0:
		drive->GetRxPDOEntry(coe_object_names::kModeOfOperation)->StoreValue(coe_drive_state_handler::ModeOfOperation::kModeProfilePosition);
		drive->GetRxPDOEntry(coe_object_names::kTargetPosition)->StoreValue(target_position_c);
        drive->GetRxPDOEntry(coe_object_names::kProfileVelocity)->StoreValue(target_velocity_c);
		

		WordBit::Write(&controlword, 8, 0);
		WordBit::Write(&controlword, 6, 0);		
		WordBit::Write(&controlword, 5, 1);	
		WordBit::Write(&controlword, 4, 0);

		if (mode_of_operation_out == coe_drive_state_handler::ModeOfOperation::kModeProfilePosition)
		{
			this->task_state++;
		}			
		break;
		case 1:
		WordBit::Write(&controlword, 4, 1);
		break;
	}

	//std::cout << "CommonMoveDriveTask<TContext>::RunTask(TContext* context): POS: " << actual_position_c << "\n";

	if (actual_position_c == target_position_c)
	{
		WordBit::Write(&controlword, 4, 0);
		context->TransitToNext();
	}
	drive->GetRxPDOEntry(coe_object_names::kControlword)->StoreValue(controlword);
}



#endif