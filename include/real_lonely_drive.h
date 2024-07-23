#ifndef REAL_LONELY_DRIVE_H
#define REAL_LONELY_DRIVE_H

#include "lonely_drive.h"

class RealLonelyDrive : public LonelyDrive
{
public:
	bool IsEmulated() override; /* always false */
	void ModifyTelemetry() override;
};


#endif