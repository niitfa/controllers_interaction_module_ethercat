#ifndef MKLKT_MODEL_H
#define MKLKT_MODEL_H

#include "device_model.h"
#include "gantry.h"
#include "kv_detector_drive.h"
#include "kv_filter_drive.h"

/* Добавить подстистему сигналов с шлюза */

class MKLKTModel : public DeviceModel
{
    Gantry* gantry = nullptr;
    KVDetectorDrive* kv_detector_drive = nullptr;
    KVFilterDrive* kv_filter_drive = nullptr;
public:
    MKLKTModel() = default;
    ~MKLKTModel() = default;

    void RegisterGantry(Gantry*);
    void RegisterKVDetectorDrive(KVDetectorDrive*);
    void RegisterKVFilterDrive(KVFilterDrive*);

    Gantry* GetGantry() const;
    KVDetectorDrive* GetKVDetectorDrive() const;
    KVFilterDrive* GetKVFilterDrive() const;
};

#endif