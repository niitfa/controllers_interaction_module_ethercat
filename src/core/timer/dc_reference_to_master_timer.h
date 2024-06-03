#ifndef DC_REFERENCE_TO_MASTER_TIMER_H
#define DC_REFERENCE_TO_MASTER_TIMER_H

#include "ethercat_timer.h"

class DCReferenceToMasterTimer : public EthercatTimer
{
	static const uint32_t kNanosecsPerSec = 1e+9;
    static const uint32_t kNanosecsPerMicrosec = 1e+3;

    bool is_timer_launched;
    uint64_t dc_time_ns;
    int32_t shift;
	timespec dcTime_ref, ts;

    EthercatSlave* reference_slave = nullptr;
	EthercatSlavesContainer* slaves = nullptr;
	EthercatMaster* master = nullptr;

    int64_t SystemTimeNanoseconds();
    int64_t TimespecToNanoseconds(timespec* ts);
    void AddNanosecondsToTimespec(uint64_t ns, timespec* ts);
public:
	DCReferenceToMasterTimer();
	void Sleep() override;
	void ConfigureClocks() override;
	void SyncDistributedClocks(EthercatMaster* master) override;
	void UpdateMasterClock() override;

    void SetMaster(EthercatMaster*);
	void SetReferenceSlaveClock(EthercatSlave*);
	void SetSlavesClocks(EthercatSlavesContainer*);
	void SetShiftMicroseconds(uint32_t);
	uint32_t GetShiftMicroseconds();

	int64_t GetCurrentTime() override;	
};


#endif