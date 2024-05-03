#ifndef CYCLE_TESTER_H
#define CYCLE_TESTER_H

#include <stdint.h>
#include <string>
#include <fstream>

class CycleTester
{
    uint32_t cycles_measured;
    uint32_t storage_size;

    std::string filename;
    std::ofstream outfile;

    uint64_t* cycle_time_ns = nullptr;
    uint64_t* calc_time_ns  = nullptr;

    uint64_t prev_begin_ns;
public:
    CycleTester();
    ~CycleTester();
    void CreateStorage(std::string filename, uint32_t size);
    void CaptureCycleBegin(uint64_t begin_time_ns);
    void CaptureCycleEnd(uint64_t end_time_ns);
    
private:
    void SaveData();

};

#endif