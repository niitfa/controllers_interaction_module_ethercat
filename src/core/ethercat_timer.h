#ifndef ETHERCATTIMER_H
#define ETHERCATTIMER_H

#include <cstdint>
#include "ecrt.h"
#include "ethercat_slaves_container.h"
#include "ethercat_master.h"

class EthercatTimer
{
	static const int MICROSECS_PER_SEC = 1e+6;
	uint32_t frequency;
	uint32_t period_us;

public:
	EthercatTimer();
	virtual ~EthercatTimer();
	
	virtual void Sleep() = 0;
	virtual void ConfigureClocks() = 0;
	virtual void SyncDistributedClocks(EthercatMaster* master) = 0;
	virtual void UpdateMasterClock() = 0;	

	void SetFrequency(uint32_t);
	void SetPeriodMicroseconds(uint32_t);	
	uint32_t GetFrequency();
	uint32_t GetPeriodMicroseconds();
};

class DCTimerMasterToReference : public EthercatTimer
{
	static const uint32_t NANOSECS_PER_MICROSEC = 1e+3;
	static const uint32_t NANOSECS_PER_SEC = 1e+9;
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
	DCTimerMasterToReference();
	void Sleep() override;
	void ConfigureClocks() override;
	void SyncDistributedClocks(EthercatMaster* master) override;
	void UpdateMasterClock() override;	

	void SetMaster(EthercatMaster*);
	void SetReferenceSlaveClock(EthercatSlave*);
	void SetSlavesClocks(EthercatSlavesContainer*);
	void SetShiftMicroseconds(uint32_t);
	uint32_t GetShiftMicroseconds();

};

class SimpleTimer : public EthercatTimer
{
public:
	void Sleep() override;
	void ConfigureClocks() override;
	void SyncDistributedClocks(EthercatMaster* master) override;
	void UpdateMasterClock() override;	
};


#endif