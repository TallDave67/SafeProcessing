#include "ProcessAgent.h"

#include <mutex>
#include <vector>
#include <thread>

std::mutex g_data_mutex;

ProcessAgent::ProcessAgent() : m_threadsafe{ false }
{
}

void ProcessAgent::process()
{
    // reset the output
    m_data.reset();

    // launch the threads
    std::vector<std::thread> threads;
    for (size_t idx = 0; idx < NUM_PRODUCERS; idx++)
    {
        std::thread t(&ProcessAgent::thread_process, this, static_cast<int>(idx + 1));
        threads.push_back(std::move(t));
    }

    for (size_t idx = 0; idx < NUM_PRODUCERS; idx++)
    {
        std::thread& t = threads[idx];
        t.join();
    }

    // write the output to file
    m_data.write_output(m_filepath);
}

void ProcessAgent::thread_process(int value)
{
    if (m_threadsafe)
    {
        g_data_mutex.lock();
        thread_do_process(value);
        g_data_mutex.unlock();
    }
    else
    {
        thread_do_process(value);
    }
}

void ProcessAgent::thread_do_process(int value)
{
    for (size_t idx = 0; idx < NUM_PRODUCERS; idx++)
    {
        m_data.add(value);
        m_delay.delay();
    }
}

