#pragma once

#include "Constants.h"

#include <array>
#include <string>

class Data
{
public:
    Data();

    void reset();
    bool add(int value);

    void write_output(std::wstring & filepath);

public:
    std::array<std::array<int, NUM_PRODUCERS * NUM_PRODUCERS>, NUM_PRODUCERS * NUM_PRODUCERS> m_data;
    size_t m_current;
};

