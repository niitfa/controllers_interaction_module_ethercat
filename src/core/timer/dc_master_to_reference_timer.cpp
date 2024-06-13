#include "dc_master_to_reference_timer.h"
#include <iostream>

#define SIGN(T) ((T > 0) - (T < 0))

DCMasterToReferenceTimer::DCMasterToReferenceTimer() : 
	EthercatTimer(),
	shift{0},
	is_timer_launched{false},	
	dc_start_time_ns{0},
	dc_time_ns{0},
	dc_started{0},
	dc_diff_ns{0},
	prev_dc_diff_ns{0},
	dc_diff_total_ns{0},
	dc_delta_total_ns{0},
	dc_filter_idx{0},
	dc_adjust_ns{0},
 	system_time_base{0},
 	wakeup_time{0},
 	overruns{0}
{}

void DCMasterToReferenceTimer::Sleep()
{
	bool wake_up_flag = false;
	uint64_t period_nanoseconds = EthercatTimer::GetPeriodMicroseconds()*kNanosecsPerMicrosec;

	while(!wake_up_flag)
	{
		if(!is_timer_launched) 
		{
	        clock_gettime(CLOCK_REALTIME, &dcTime_ref);
	        AddNanosecondsToTimespec(10*period_nanoseconds, &dcTime_ref);
	        is_timer_launched = true;
	    }

	    int64_t dcTime_curr_ns = SystemTimeNanoseconds();
	    int64_t cycle_diff_ns = TimespecToNanoseconds(&dcTime_ref) - dcTime_curr_ns;
        /*std::cout
                 << "dcTime_curr_ns: " << dcTime_curr_ns % kNanosecsPerSec
                 << "\tTimespecToNanoseconds(&dcTime_ref): " << TimespecToNanoseconds(&dcTime_ref) % kNanosecsPerSec
                 << "\tcycle_diff_ns: " << cycle_diff_ns % kNanosecsPerSec << std::endl; */
               
	    if(cycle_diff_ns <= 0)
	    {   
            //std::cout << "! cycle_diff_ns: " << cycle_diff_ns % kNanosecsPerSec << std::endl;;
	    	AddNanosecondsToTimespec(period_nanoseconds, &dcTime_ref);
			wake_up_flag = true;	
	    }
	}
}

void DCMasterToReferenceTimer::ConfigureClocks()
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

void DCMasterToReferenceTimer::SyncDistributedClocks(EthercatMaster* master)
{
    uint32_t ref_time = 0;
    uint64_t prev_app_time = dc_time_ns;
    dc_time_ns = this->SystemTimeNanoseconds();

    if (this->master)
    {
    	ecrt_master_application_time(master->GetRequest(), dc_time_ns);
    	ecrt_master_reference_clock_time(master->GetRequest(), &ref_time);
	}
    dc_diff_ns = (uint32_t)prev_app_time - ref_time;

    if (this->master)
    {
    	ecrt_master_sync_slave_clocks(master->GetRequest());
    }
}

void DCMasterToReferenceTimer::UpdateMasterClock()
{
	//printf("system_time_base: %i\n", system_time_base);
	uint64_t period_nanoseconds = EthercatTimer::GetPeriodMicroseconds()*kNanosecsPerMicrosec;
    int32_t delta = dc_diff_ns - prev_dc_diff_ns;
    prev_dc_diff_ns = dc_diff_ns;

    // normalise the time diff
    dc_diff_ns =
        ((dc_diff_ns + (period_nanoseconds / 2)) % period_nanoseconds) - (period_nanoseconds / 2);
        
    //printf("dc_diff_ns: %i\n",dc_diff_ns); // akg 
        
    // only update if primary master
    if (dc_started)
    {
        // add to totals
        dc_diff_total_ns += dc_diff_ns;
        dc_delta_total_ns += delta;
        dc_filter_idx++;

        if (dc_filter_idx >= DC_FILTER_CNT)
        {
            // add rounded delta average
            dc_adjust_ns +=
                ((dc_delta_total_ns + (DC_FILTER_CNT / 2)) / DC_FILTER_CNT);

            // and add adjustment for general diff (to pull in drift)
            dc_adjust_ns += SIGN(dc_diff_total_ns / DC_FILTER_CNT);
            //printf("dc_adjust_ns: %i\n", dc_adjust_ns);

            // limit crazy numbers (0.1% of std cycle time)
            if (dc_adjust_ns < -1000)
            {
                dc_adjust_ns = -1000;
            }
            if (dc_adjust_ns > 1000)
            {
                dc_adjust_ns = 1000;
            }

            dc_diff_total_ns = 0LL;
            dc_delta_total_ns = 0LL;
            dc_filter_idx = 0;
        }
        system_time_base += dc_adjust_ns + 5*SIGN(dc_diff_ns);
    }
    else
    {
        dc_started = (dc_diff_ns != 0);
        if (dc_started)
        {
            dc_start_time_ns = dc_time_ns;
        }
    }
}	

int64_t DCMasterToReferenceTimer::SystemTimeNanoseconds()
{
	clock_gettime(CLOCK_REALTIME, &ts);
    return TimespecToNanoseconds(&ts) - system_time_base;
}

int64_t DCMasterToReferenceTimer::TimespecToNanoseconds(timespec* ts)
{
	return (uint64_t) ts->tv_sec * kNanosecsPerSec + ts->tv_nsec;
}

void DCMasterToReferenceTimer::AddNanosecondsToTimespec(uint64_t ns, timespec* ts)
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

void DCMasterToReferenceTimer::SetMaster(EthercatMaster* master)
{
    this->master = master;
}

void DCMasterToReferenceTimer::SetReferenceSlaveClock(EthercatSlave* slave) 
{
    this->reference_slave = slave;
}

void DCMasterToReferenceTimer::SetSlavesClocks(EthercatSlavesContainer* slaves) 
{
    this->slaves = slaves;
}

void DCMasterToReferenceTimer::SetShiftMicroseconds(uint32_t shift) 
{
    this->shift = shift;
}

uint32_t DCMasterToReferenceTimer::GetShiftMicroseconds() 
{
    return this->shift;
}

int64_t DCMasterToReferenceTimer::GetCurrentTime()
{
    return SystemTimeNanoseconds();
}