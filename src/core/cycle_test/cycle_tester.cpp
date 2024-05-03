#include "cycle_tester.h"
#include <fstream>

CycleTester::CycleTester()
{
    this->cycles_measured = 0;
    this->storage_size = 0;

    this->prev_begin_ns = 0;
}

CycleTester::~CycleTester()
{
    this->cycles_measured = 0;
    this->storage_size = 0;
    delete[] this->cycle_time_ns;
    delete[] this->calc_time_ns;
}

void CycleTester::CreateStorage(std::string filename, uint32_t size)
{
    if (!cycle_time_ns && !calc_time_ns)
    {
        this->storage_size = size;
        this->cycle_time_ns = new uint64_t[this->storage_size]{};
        this->calc_time_ns = new uint64_t[this->storage_size]{};
        
        outfile.open(filename);
    }
}

void CycleTester::CaptureCycleBegin(uint64_t begin_time_ns)
{
    if(cycles_measured && this->cycles_measured <= this->storage_size)
    {
        this->cycle_time_ns[cycles_measured - 1] = begin_time_ns - this->prev_begin_ns;
    }

    if(this->cycles_measured == this->storage_size + 1)
    {
        this->SaveData();
    }

    this->prev_begin_ns = begin_time_ns;
    this->cycles_measured++;
}

void CycleTester::CaptureCycleEnd(uint64_t end_time_ns)
{
    if(0 < this->cycles_measured < this->storage_size)
    {
        this->calc_time_ns[cycles_measured - 1] = end_time_ns - this->prev_begin_ns;
    }  
}

void CycleTester::SaveData()
{
    for(int i = 0; i < storage_size; ++i)
    {
        outfile << cycle_time_ns[i] << '\t' << calc_time_ns[i] << '\n';
    }
    outfile.close();

    delete[] cycle_time_ns;
    delete[] calc_time_ns;
}