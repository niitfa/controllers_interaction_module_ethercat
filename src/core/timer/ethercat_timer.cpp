#include "ethercat_timer.h"
#include <chrono>
#include <thread>
#include <iostream>

EthercatTimer::EthercatTimer() : frequency{0} {}

EthercatTimer::~EthercatTimer() = default;

void EthercatTimer::SetFrequency(uint32_t frequency)
{
	this->frequency = frequency;
	this->period_us = MICROSECS_PER_SEC / frequency;
}

void EthercatTimer::SetPeriodMicroseconds(uint32_t period_us)
{	
	this->period_us = period_us;
	this->frequency = MICROSECS_PER_SEC / period_us;
}

uint32_t EthercatTimer::GetFrequency()
{
	return this->frequency;
}

uint32_t EthercatTimer::GetPeriodMicroseconds()
{
	return this->period_us;
}


// DistributedClocksTimer


// SimpleTimer
void SimpleTimer::Sleep()
{
	std::chrono::microseconds us(
		EthercatTimer::GetPeriodMicroseconds()
		);
	std::this_thread::sleep_for(us);
}

void SimpleTimer::ConfigureClocks()
{}

void SimpleTimer::SyncDistributedClocks(EthercatMaster* master)
{}

void SimpleTimer::UpdateMasterClock()
{}