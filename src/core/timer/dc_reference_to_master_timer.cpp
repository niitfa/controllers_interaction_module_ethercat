#include "dc_reference_to_master_timer.h"

DCReferenceToMasterTimer::DCReferenceToMasterTimer() : 
    is_timer_launched{false},
    dc_time_ns{0},
    shift{0},
    dcTime_ref{0, 0},  
    ts{0, 0}
{}

void DCReferenceToMasterTimer::Sleep()
{
	bool wake_up_flag = false;
	uint64_t period_nanoseconds = EthercatTimer::GetPeriodMicroseconds()*kNanosecsPerMicrosec;

	while(!wake_up_flag)
	{
		if(!is_timer_launched) 
		{
	        clock_gettime(CLOCK_REALTIME, &dcTime_ref);
	        AddNanosecondsToTimespec(period_nanoseconds, &dcTime_ref);
	        is_timer_launched = true;
	    }

	    int64_t dcTime_curr_ns = SystemTimeNanoseconds();
	    int64_t cycle_diff_ns = TimespecToNanoseconds(&dcTime_ref) - dcTime_curr_ns;
        //std::cout << "ref time: " << TimespecToNanoseconds(&dcTime_ref) << "\tcycle_diff_ns:" <<
        //       cycle_diff_ns << std::endl;
	    if(cycle_diff_ns <= 0)
	    {
            //std::cout << "!\n";
	    	AddNanosecondsToTimespec(period_nanoseconds, &dcTime_ref);
			wake_up_flag = true;	
	    }
	}
}

void DCReferenceToMasterTimer::ConfigureClocks()
{
 	auto slaves_map = this->slaves->GetMap();
	for (auto it = slaves_map->begin(); it != slaves_map->end(); ++it)
	{
        if(it->second->HasEnabledDistributedClocks())
        {
            //std::cout << "DCMasterToReferenceTimer::ConfigureClocks(): name = " << it->second->GetName() << " " << it->second->GetConfig() << std::endl;
            ecrt_slave_config_dc(
                it->second->GetConfig(),
                it->second->GetAssignActivate(),
                this->EthercatTimer::GetPeriodMicroseconds() * kNanosecsPerMicrosec, 
                this->GetShiftMicroseconds() * kNanosecsPerMicrosec,
                0,//this->EthercatTimer::GetPeriodMicroseconds() * kNanosecsPerMicrosec, 
                0);
        }
	}
	if(this->master && this->reference_slave)
	{
        ec_slave_config_t* sc_ref = nullptr; 
        if(this->reference_slave)
        {
            sc_ref = this->reference_slave->GetConfig();
        }
        //std::cout << "DCMasterToReferenceTimer::ConfigureClocks(): ref name = " << reference_slave->GetName() << " " << reference_slave->GetConfig() << std::endl;
		if(ecrt_master_select_reference_clock(
			this->master->GetRequest(),
			sc_ref))
		{
			std::cerr << ">>> Ethercat: failed to select reference clock.\n";
		}
	}   
}

void DCReferenceToMasterTimer::SyncDistributedClocks(EthercatMaster* master)
{
    this->dc_time_ns = SystemTimeNanoseconds();
    ecrt_master_application_time(master->GetRequest(), dc_time_ns);
    ecrt_master_sync_reference_clock(master->GetRequest());

    /* Additional */

    ecrt_master_sync_slave_clocks(master->GetRequest());
    //ecrt_master_sync_monitor_queue(master->GetRequest());
    //uint32_t res = ecrt_master_sync_monitor_process(master->GetRequest());
    //std::cout << "DCReferenceToMasterTimer::SyncDistributedClocks: res = " << res << std::endl;

}

int64_t DCReferenceToMasterTimer::SystemTimeNanoseconds()
{
	clock_gettime(CLOCK_REALTIME, &ts);
    return TimespecToNanoseconds(&ts);
}

int64_t DCReferenceToMasterTimer::TimespecToNanoseconds(timespec* ts)
{
	return (uint64_t) ts->tv_sec * kNanosecsPerSec + ts->tv_nsec;
}

void DCReferenceToMasterTimer::AddNanosecondsToTimespec(uint64_t ns, timespec* ts)
{
	ts->tv_sec += ns / kNanosecsPerSec; // ts.tv_sec = ts.tv_sec + nanosecs / NSECS_IN_SEC
    ns = ns % kNanosecsPerSec;
    
    if(ts->tv_nsec + ns > kNanosecsPerSec) {
        ts->tv_sec += 1;
        ts->tv_nsec += (ns - kNanosecsPerSec);
    }
    else
    {
        ts->tv_nsec += ns;
    }
}

void DCReferenceToMasterTimer::UpdateMasterClock()
{}	

void DCReferenceToMasterTimer::SetMaster(EthercatMaster* master)
{
    this->master = master;
}

void DCReferenceToMasterTimer::SetReferenceSlaveClock(EthercatSlave* slave) 
{
    this->reference_slave = slave;
}

void DCReferenceToMasterTimer::SetSlavesClocks(EthercatSlavesContainer* slaves) 
{
    this->slaves = slaves;
}

void DCReferenceToMasterTimer::SetShiftMicroseconds(uint32_t shift) 
{
    this->shift = shift;
}

uint32_t DCReferenceToMasterTimer::GetShiftMicroseconds() 
{
    return this->shift;
}

int64_t DCReferenceToMasterTimer::GetCurrentTime()
{
    return SystemTimeNanoseconds();
}