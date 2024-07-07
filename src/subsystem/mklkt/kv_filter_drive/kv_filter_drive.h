#ifndef KV_FILTER_DRIVE_H
#define KV_FILTER_DRIVE_H

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "kv_filter_drive_telemetry.h"
#include "kv_filter_drive_task.h"
#include "kv_filter_drive_context.h"

#include "wire_sensor.h"
#include "ethercat_slave.h"

/*
    TO DO:
    1) Концевики (из данных драйвера)
    2)
*/

class KVFilterDrive : public SubsystemContentCreator<KVFilterDriveContext, KVFilterDriveTask, KVFilterDrive, KVFilterDriveTelemetry>
{
public:
    struct Properties
    {
        uint32_t microstep_resolution = 0;
        float thread_pitch = 0;
    };
protected:
    Properties props;
    WireSensor* wire_sensor = nullptr;
    EthercatSlave* drive = nullptr;
public:
    KVFilterDrive() = delete;
    KVFilterDrive(uint32_t microstep_resolution, float thread_pitch);
    ~KVFilterDrive();
    void Action() override;
    Properties GetProperties();
    void RegisterWireSensor(WireSensor* sensor);
    void RegisterDrive(EthercatSlave* drive);
    EthercatSlave* GetDrive();
};

#endif