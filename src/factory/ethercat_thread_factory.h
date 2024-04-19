#ifndef ETHERCAT_THREAD_FACTORY_H
#define ETHERCAT_THREAD_FACTORY_H

#include "ethercat_thread_manager.h"
#include "lonely_drive.h"
#include "unspecified_device.h"


void ConfigureNetwork_0(EthercatThreadManager* thread, UnspecifiedDevice* device,  LonelyDrive* mech_subsystem);
void ConfigureNetwork_1(EthercatThreadManager* thread, UnspecifiedDevice* device,  LonelyDrive* mech_subsystem);

#endif