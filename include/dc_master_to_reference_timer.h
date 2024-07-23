#ifndef DC_MASTER_TO_REFERENCE_TIMER_H
#define DC_MASTER_TO_REFERENCE_TIMER_H

#include "ethercat_timer.h"

class DCMasterToReferenceTimer : public EthercatTimer
{
	static const uint32_t kNanosecsPerMicrosec = 1e+3;
	static const uint32_t kNanosecsPerSec = 1e+9;
	static const uint32_t DC_FILTER_CNT = 1024;

	EthercatSlave* reference_slave = nullptr;
	EthercatSlavesContainer* slaves = nullptr;
	EthercatMaster* master = nullptr;
	uint32_t shift;

	bool is_timer_launched;
	timespec dcTime_ref, ts;
	uint64_t dc_start_time_ns;
	uint64_t dc_time_ns;
 	uint8_t dc_started;
 	int32_t dc_diff_ns;
 	int32_t prev_dc_diff_ns;
 	int64_t dc_diff_total_ns;
 	int64_t dc_delta_total_ns;
 	int32_t dc_filter_idx;
 	int64_t dc_adjust_ns;
 	int64_t system_time_base;
 	uint64_t wakeup_time;
 	uint64_t overruns;

 	int64_t SystemTimeNanoseconds();
 	int64_t TimespecToNanoseconds(timespec*);
 	void AddNanosecondsToTimespec(uint64_t, timespec*);
public:
	DCMasterToReferenceTimer();
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