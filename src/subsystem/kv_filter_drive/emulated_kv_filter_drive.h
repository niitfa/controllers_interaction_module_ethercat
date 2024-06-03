#ifndef EMULATED_KV_FILTER_DRIVE_H
#define EMULATED_KV_FILTER_DRIVE_H

#include "kv_filter_drive.h"

class EmulatedKVFilterDrive : public KVFilterDrive
{
public:
    bool IsEmulated() override;
    void ModifyTelemetry() override;
};

#endif