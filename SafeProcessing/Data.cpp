#include "Data.h"

#include <iostream>
#include <fstream>

Data::Data()
{
    reset();
}

void Data::reset()
{
    for (auto& row : m_data)
    {
        for (auto& col : row)
        {
            col = 0;
        }
    }

    m_current = 0;
}

bool Data::add(int value)
{
    bool ret = false;
    if (m_current < m_data.size())
    {
        ret = true;
        for (auto& col : m_data[m_current])
        {
            col = value;
        }
        m_current++;
    }
    return ret;
}

void Data::write_output(std::wstring& filepath)
{
    // Create and open a text file
    std::ofstream output_file(filepath);

    // Write to the file
    for (auto& row : m_data)
    {
        for (auto& col : row)
        {
            output_file << col << " ";
        }
        output_file << std::endl;
    }

    // Close the file
    output_file.close();
}