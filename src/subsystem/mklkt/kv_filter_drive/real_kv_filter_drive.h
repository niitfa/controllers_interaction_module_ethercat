#ifndef REAL_KV_FILTER_DRIVE_H
#define REAL_KV_FILTER_DRIVE_H

#include "kv_filter_drive.h"
#include "wire_sensor.h"
#include "ethercat_slave.h"

class RealKVFilterDrive : public KVFilterDrive
{
public:
    RealKVFilterDrive(uint32_t microstep_resolution, float thread_pitch);
    bool IsEmulated() override;
    //void Action() override;
	void ModifyTelemetry() override;

   // void RegisterWireSensor(WireSensor* sensor);
   // void RegisterDrive(EthercatSlave* drive);
};

#endif