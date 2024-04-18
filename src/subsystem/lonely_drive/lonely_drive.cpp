#include "lonely_drive.h"
#include "coe_drive_state_handler.h"

using namespace coe_drive_state_handler;

void LonelyDrive::RegisterDrive(EthercatSlave* drive)
{
	this->drive = drive;
}

EthercatSlave* LonelyDrive::GetDrive()
{
	return this->drive;
}

