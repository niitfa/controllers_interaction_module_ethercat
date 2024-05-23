#ifndef WIRE_SENSOR_H
#define WIRE_SENSOR_H

#include <stdint.h>
#include <vector>

class WireSensor
{
    uint16_t frequency = 1; // частота сети (нужна? или обращаться к таймеру?
    uint16_t averaging_level; // сколько шагов назад отсчитывать для вычисления скорости

    float power_supply_V = 1;
    float output_mV_per_V_per_mm = 1;
    float volt_per_count = 1;

    std::vector<int64_t> last_positions;
    std::vector<int64_t>::iterator it_current;
    std::vector<int64_t>::iterator it_previous;

    int64_t* p_position_counts = nullptr; // показания позиции энкодера из ethercat-пакета
    float velocity_counts_per_sec = 0;
public:
    WireSensor(uint16_t averaging_level);
    ~WireSensor() = default;
    void Update();

    int64_t GetPositionCounts();
    int64_t GetVelocityCountsPerSec(); 
    float GetPositionMillimeters();
    float GetVelociyMillimetersPerSec();

    void SetPositionAddress(int64_t* address);
    void SetPowerSupply(float power_supply_V);
    void SetOutput(float output);
    void SetAveragingLevel(uint16_t level);
    void SetFrequency(uint16_t frequency);
    void SetVoltPerCount(float volt_per_count);
};

#endif