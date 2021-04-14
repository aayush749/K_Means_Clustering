#ifndef TIMING_HPP
#define TIMING_HPP

#include <iostream>
#include <chrono>

struct Timer
{
private:
    std::string m_FunctionName;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration;
public:
    Timer(const char* function_name)
        :m_FunctionName(function_name)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    Timer()
        :m_FunctionName(0)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        
        float ms = duration.count() * 1000;
        if(m_FunctionName.length())
            printf("%s() took %f ms.\n", m_FunctionName.c_str(), ms);
        else
            printf("Timer clocked %f ms.\n", ms);
    }
};

#endif