#include "calculation_task.h"
#include <cstdlib>
#include <ctime>

void CalculationTask::StateRun()
{
    int64_t a;  
    std::srand(std::time(nullptr));

    int iterations = 10000;

    for(int i = 0; i < iterations; ++i)
    {
        /* std::rand = [0, 2147483647] */
        a = std::rand() * std::rand();
    }
}