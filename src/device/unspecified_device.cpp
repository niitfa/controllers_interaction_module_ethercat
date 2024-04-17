#include "unspecified_device.h"

void UnspecifiedDevice::RegisterSubsystem(Subsystem* ext_subsystem)
{
	Subsystem* plug_pointer = nullptr;
	DeviceModel::RegisterSubsystem(ext_subsystem, &plug_pointer);
}
