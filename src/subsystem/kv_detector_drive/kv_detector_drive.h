#ifndef KV_DETECTOR_DRIVE_H
#define KV_DETECTOR_DRIVE_H

#include "debug_logger.h"

#include "subsystem_content_creator.h"
#include "subsystem_state_selector.h"

#include "kv_detector_drive_telemetry.h"
#include "kv_detector_drive_task.h"
#include "kv_detector_drive_context.h"

#include "wire_sensor.h"
#include "ethercat_slave.h"

class KVDetectorDrive : public SubsystemContentCreator<KVDetectorDriveContext, KVDetectorDriveTask, KVDetectorDrive, KVDetectorDriveTelemetry>
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
    DebugLogger<float> logger; // debug!!
public:
    KVDetectorDrive() = delete;
    KVDetectorDrive(uint32_t microstep_resolution, float thread_pitch);
    ~KVDetectorDrive();
    void Action() override;
    Properties GetProperties();
    void RegisterWireSensor(WireSensor* sensor);
    void RegisterDrive(EthercatSlave* drive);
    EthercatSlave* GetDrive();
};

#endif