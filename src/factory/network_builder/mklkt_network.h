#ifndef MKLKT_NETWORK_H
#define MKLKT_NETWORK_H

#include "mklkt_model.h"
#include "ethercat_thread_manager.h"

class MKLKTNetwork
{
    EthercatThreadManager* thread = nullptr;
    MKLKTModel* device = nullptr;

    bool is_gantry_emulated = false;
    bool is_kv_detector_emulated = false;
    bool is_kv_filter_emulated = false;

    bool started = false;
public:
    MKLKTNetwork() = default;
    ~MKLKTNetwork();

    void Build(uint16_t master_index);

    void StartThread();
    void StopThread();
    /**
     * @brief Enables/disables gantry emulation.
     * @warning Call this method in non-realtime context 
     * (before calling StartThread() method of after calling StopThread() method) 
     */
    void SetGantryEmulationStatus(bool status);

    /**
     * @brief Enables/disables kv detector drive emulation.
     * @warning Call this method in non-realtime context 
     * (before calling StartThread() method of after calling StopThread() method) 
     */
    void SetKVDetectorDriveEmulatonStatus(bool status);

    /**
     * @brief Enables/disables kv filter drive emulation.
     * @warning Call this method in non-realtime context 
     * (before calling StartThread() method of after calling StopThread() method) 
     */
    void SetKVFilterDriveEmulatonStatus(bool status);

    MKLKTModel* GetDevice();
};

#endif