#ifndef EMULATED_LONELY_DRIVE_H
#define EMULATED_LONELY_DRIVE_H

#include "lonely_drive.h"

class EmulatedLonelyDrive : public LonelyDrive
{
public:
	bool IsEmulated() override; /* always true */
	void ModifyTelemetry() override;
};



#endif