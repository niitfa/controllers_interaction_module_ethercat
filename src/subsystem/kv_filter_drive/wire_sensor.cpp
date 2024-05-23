#include "wire_sensor.h"
#include <iostream>

WireSensor::WireSensor(uint16_t averaging_level)
{
    this->averaging_level = std::max((uint16_t)1, averaging_level);
    
    this->last_positions = std::vector<int64_t>(averaging_level + 1, 0);
    this->it_current = last_positions.begin();
    this->it_previous = it_current + 1;
}

void WireSensor::Update()
{
    *it_current = *p_position_counts; 

    velocity_counts_per_sec = (float)(*it_current - *it_previous) / averaging_level * frequency;

    std::cout << "WireSensor::Update(): Wire sensor val: "
     << GetPositionCounts() << std::endl;

    it_current + 1  == last_positions.end() ? it_current = last_positions.begin() : ++it_current;
    it_previous + 1 == last_positions.end() ? it_previous = last_positions.begin() : ++it_previous;
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
    return GetPositionCounts() * volt_per_count / output_mV_per_V_per_mm / power_supply_V * 1000;
}

float WireSensor::GetVelociyMillimetersPerSec()
{
    return GetVelocityCountsPerSec() * volt_per_count / output_mV_per_V_per_mm / power_supply_V * 1000;
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
