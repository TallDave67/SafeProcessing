#pragma once
#include <string>

#include "Data.h"
#include "Delay.h"

class ProcessAgent
{
public:
    ProcessAgent();
    void process();

private:
    void do_process();
    void thread_process(int value);
    void thread_do_process(int value);

public:
    std::wstring m_filepath;
    bool m_threadsafe;
    Data m_data;
    Delay m_delay;
};

