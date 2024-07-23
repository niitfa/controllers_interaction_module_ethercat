#ifndef SIMPLE_MOVING_AVERAGE_HANDLER_H
#define SIMPLE_MOVING_AVERAGE_HANDLER_H

#include <vector>
#include <iostream>

template<typename T>
class SimpleMovingAverageHandler
{
    T average_value;
    uint32_t size = 2;
    T* last_data = nullptr;
    uint32_t index_current = 0;
    uint32_t index_last = index_current + 1;
public:
    SimpleMovingAverageHandler(uint32_t size)
    {
        average_value = 0;
        this->size = std::max((uint32_t)1, size) + 1;
        this->last_data = new T[this->size];
    }
    ~SimpleMovingAverageHandler()
    {
        delete [] last_data;
    }

    void PlaceNextValue(T val)
    {
        last_data[index_current] = val;
        average_value = average_value + (last_data[index_current] - last_data[index_last]) / (size - 1);
        IncrementIndexCyclically(index_current);
        IncrementIndexCyclically(index_last);
    }

    T GetMovingAverage()
    {
        return this->average_value;
    }

private:
    void IncrementIndexCyclically(uint32_t& index)
    {
        index == (size - 1) ? index = 0 : ++index;
    }
};

#endif