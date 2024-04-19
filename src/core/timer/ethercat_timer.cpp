#include "ethercat_timer.h"
#include <chrono>
#include <thread>
#include <iostream>

EthercatTimer::EthercatTimer() : frequency{0}
{
}

EthercatTimer::~EthercatTimer() = default;

void EthercatTimer::SetFrequency(uint32_t frequency)
{
	this->frequency = frequency;
	this->period_us = kMicrosecsPerSec / frequency;
}

void EthercatTimer::SetPeriodMicroseconds(uint32_t period_us)
{	
	this->period_us = period_us;
	this->frequency = kMicrosecsPerSec / period_us;
}

uint32_t EthercatTimer::GetFrequency()
{
	return this->frequency;
}

uint32_t EthercatTimer::GetPeriodMicroseconds()
{
	return this->period_us;
}