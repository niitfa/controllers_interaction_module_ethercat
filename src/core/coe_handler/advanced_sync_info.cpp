#include "advanced_sync_info.h"
#include <iostream>

void AdvancedSyncInfo::DisableSM0()
{
    this->SM0_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM1()
{
    this->SM1_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM2()
{
    this->SM2_is_enabled = false;
}

void AdvancedSyncInfo::DisableSM3()
{
    this->SM3_is_enabled = false;
}

void AdvancedSyncInfo::Create()
{
    this->DefaultSyncInfo::PreparePDOs();

    uint16_t sync_size = 1 + SM0_is_enabled + SM1_is_enabled + SM2_is_enabled + SM3_is_enabled;
    syncs = new ec_sync_info_t[sync_size];

    uint8_t i = 0;
    if(SM0_is_enabled) {
        syncs[i] = {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE};
        //printf("sm0 index: %i\n", i);
        ++i;
    }
    if(SM1_is_enabled) {
        syncs[i] = {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE};
        //printf("sm1 index: %i\n", i);
        ++i;
    }
    if(SM2_is_enabled) {
        syncs[i] = {2, EC_DIR_OUTPUT, 1, ec_rxpdo, EC_WD_ENABLE};
        //printf("sm2 index: %i\n", i);
        ++i;
    }
    if(SM3_is_enabled) {
        syncs[i] = {3, EC_DIR_INPUT, 1, ec_txpdo, EC_WD_DISABLE};
        //printf("sm3 index: %i\n", i);
        ++i;
    }
    syncs[i] = {0xff};

    this->SyncInfo::size = sync_size;
}