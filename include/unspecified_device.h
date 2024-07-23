#ifndef UNSPECIFIED_DEVICE_H
#define UNSPECIFIED_DEVICE_H

#include "device_model.h"

class UnspecifiedDevice : public DeviceModel
{
public:
	void RegisterSubsystem(Subsystem* ext_subsystem);
};

#endif