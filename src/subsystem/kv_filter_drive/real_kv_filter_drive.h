#ifndef REAL_KV_FILTER_DRIVE_H
#define REAL_KV_FILTER_DRIVE_H

#include "kv_filter_drive.h"
#include "wire_sensor.h"
#include "ethercat_slave.h"

class RealKVFilterDrive : public KVFilterDrive
{
    WireSensor* wire_sensor = nullptr;
    EthercatSlave* drive = nullptr;
public:
    ~RealKVFilterDrive();
    bool IsEmulated() override;
    void RegisterWireSensor(WireSensor* sensor);
    void RegisterDrive(EthercatSlave* drive);
    void Action() override;
    void UpdateSubsystemTelemetry() override;
	void ModifyTelemetry() override;
};

#endif