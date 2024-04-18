#ifndef LONELY_DRIVE_EMULATION_H
#define LONELY_DRIVE_EMULATION_H

#include "emulated_event_content_creator.h"
#include "lonely_drive_task_context.h"

class LonelyDriveEmulation : public EmulatedEventContentCleator<LonelyDriveTaskContext>
{};

#endif