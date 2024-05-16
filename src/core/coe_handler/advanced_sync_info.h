#ifndef ADVANCED_SYNC_INFO_H
#define ADVANCED_SYNC_INFO_H

#include "default_sync_info.h"
#include <vector>

class AdvancedSyncInfo : public DefaultSyncInfo
{
    bool SM0_is_enabled = true;
    bool SM1_is_enabled = true;
    bool SM2_is_enabled = true;
    bool SM3_is_enabled = true;
public:
    AdvancedSyncInfo() = default;
    ~AdvancedSyncInfo() = default;

    void DisableSM0();
    void DisableSM1();
    void DisableSM2();
    void DisableSM3();

    void Create() override;
};

#endif