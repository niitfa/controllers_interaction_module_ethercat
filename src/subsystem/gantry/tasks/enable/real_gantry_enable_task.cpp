#include "gantry_enable_task.h"

void RealGantryEnableTask::StateRun()
{
	std::cout << "Real gantry enabling...\n" ; 
	GantryTaskState::GetContext()->TransitToNext();
}