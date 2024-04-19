#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include "ethercat_timer.h"

class SimpleTimer : public EthercatTimer
{
public:
	void Sleep() override;
	void ConfigureClocks() override;
	void SyncDistributedClocks(EthercatMaster* master) override;
	void UpdateMasterClock() override;	
};

#endif