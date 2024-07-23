#ifndef LONELY_DRIVE_TEST_EMULATION_H
#define LONELY_DRIVE_TEST_EMULATION_H

#include "lonely_drive_emulation.h"

class LonelyDriveTestEmulation : public LonelyDriveEmulation
{
	int cnt;
public:
	LonelyDriveTestEmulation();
	~LonelyDriveTestEmulation() = default;
	void RunEvent() override;
};

#endif