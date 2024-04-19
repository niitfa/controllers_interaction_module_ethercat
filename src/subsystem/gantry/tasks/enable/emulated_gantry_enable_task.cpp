#include "gantry_enable_task.h"

void EmulatedGantryEnableTask::StateRun()
{
    std::cout << "Emulated gantry enabling...\n" ; 
	GantryTaskState::GetContext()->TransitToNext();
}