#ifndef REAL_KV_DETECTOR_DRIVE_H
#define REAL_KV_DETECTOR_DRIVE_H

#include "kv_detector_drive.h"
#include "wire_sensor.h"
#include "ethercat_slave.h"

class RealKVDetectorDrive : public KVDetectorDrive
{
public:
    RealKVDetectorDrive(uint32_t microstep_resolution, float thread_pitch);
    bool IsEmulated() override;
	void ModifyTelemetry() override;
};

#endif