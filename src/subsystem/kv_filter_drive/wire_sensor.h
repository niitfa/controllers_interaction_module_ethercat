#ifndef WIRE_SENSOR_H
#define WIRE_SENSOR_H

#include <stdint.h>
#include <vector>
#include "simple_moving_average_handler.h"

class WireSensor
{
    static const int kMillivoltsPerVolt = 1000;
    uint16_t frequency = 1; // частота сети (нужна? или обращаться к таймеру?)
    uint16_t averaging_level; // кол-во точек для вычисления скольящего среднего

    float power_supply_V = 1;
    float output_mV_per_V_per_mm = 1;
    float volt_per_count = 1;

    SimpleMovingAverageHandler<float>* SMA_position{nullptr};

    int64_t* p_position_counts = nullptr; // показания позиции энкодера из ethercat-пакета
    float velocity_counts_per_sec = 0;
public:
    WireSensor(uint16_t averaging_level);
    ~WireSensor();
    void Update();

    int64_t GetPositionCounts();
    int64_t GetVelocityCountsPerSec(); 
    float GetPositionMillimeters();
    float GetVelociyMillimetersPerSec();

    void SetPositionAddress(int64_t* address);
    void SetPowerSupply(float power_supply_V);
    void SetOutput(float output);
    void SetFrequency(uint16_t frequency);
    void SetVoltPerCount(float volt_per_count);
};

#endif