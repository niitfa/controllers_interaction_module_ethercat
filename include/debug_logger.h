#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <string>
#include <fstream>
#include <vector>
#include <thread>

template<typename T>
class DebugLogger
{
    T** data = nullptr;

    uint16_t number_of_values = 0;
    uint32_t size = 0;
    std::string filename;
    std::ofstream outfile;

    uint32_t current_index = 0;
    
public:
    DebugLogger() = default;
    ~DebugLogger()
    {
        if(data)
        {
            for(int i = 0; i < number_of_values; i++)
            {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    void CreateStorage(uint16_t number_of_values, uint32_t size, std::string filename)
    {
        this->number_of_values = number_of_values;
        this->size = size;
        this->filename = filename;
        this->outfile.open(filename);

        data = new T*[number_of_values];
        for(int i = 0; i < number_of_values; i++)
        {
            data[i] = new T[size]{0};
        }   
    }

    void PlaceData(std::vector<T> vec_data)
    {
        if(current_index < size)
        {
            for (int i = 0; i < std::min(number_of_values, (uint16_t)vec_data.size()); i++)
            {
                data[i][current_index] = vec_data[i];
            }
            current_index++;
        }
        if(current_index == size)
        {
            this->SaveData();
            current_index++;
        }

    }

private:
    void SaveData()
    {
        for(uint32_t i = 0; i < size; ++i)
        {
            for(uint16_t j = 0; j < number_of_values; j++)
            {
                outfile << data[j][i] << "\t";
            }
            outfile << "\n";
        }
        outfile.close();
    }

};

#endif