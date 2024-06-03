#include "wire_sensor.h"
#include <iostream>

WireSensor::WireSensor(uint16_t averaging_level)
{
    this->averaging_level = std::max((uint16_t)1, averaging_level);
    SMA_position = new SimpleMovingAverageHandler<float>(averaging_level);
}

WireSensor::~WireSensor()
{
    delete SMA_position;
}

void WireSensor::Update()
{
    float previous_sma_position = SMA_position->GetMovingAverage();
    SMA_position->PlaceNextValue((float)GetPositionCounts());
    velocity_counts_per_sec = (SMA_position->GetMovingAverage() - previous_sma_position) * frequency; 
    //std::cout << "WireSensor::Update(): val = " << GetVelociyMillimetersPerSec() << std::endl;
}

int64_t WireSensor::GetPositionCounts()
{
    if(this->p_position_counts)
    {
        return *p_position_counts;
    }
    else
    {
        return 0;
    }
}

int64_t WireSensor::GetVelocityCountsPerSec()
{
    return this->velocity_counts_per_sec;
}

float WireSensor::GetPositionMillimeters()
{
    return GetPositionCounts() * volt_per_count * kMillivoltsPerVolt / output_mV_per_V_per_mm / power_supply_V;
}

float WireSensor::GetVelociyMillimetersPerSec()
{
    return GetVelocityCountsPerSec() * volt_per_count * kMillivoltsPerVolt / output_mV_per_V_per_mm / power_supply_V;
}

void WireSensor::SetPositionAddress(int64_t* address)
{
    this->p_position_counts = address;
}

void WireSensor::SetPowerSupply(float power_supply_V)
{
    this->power_supply_V = power_supply_V;
}

void WireSensor::SetOutput(float output)
{
    this->output_mV_per_V_per_mm = output;
}

void WireSensor::SetFrequency(uint16_t frequency)
{
    this->frequency = frequency;
}

void WireSensor::SetVoltPerCount(float volt_per_count)
{
    this->volt_per_count = volt_per_count;
}
