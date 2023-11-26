#pragma once

#include <winerror.h>
#include <string>

#include "ProcessAgent.h"

class Process
{
public:
    Process();
    HRESULT process();

public:
    ProcessAgent m_agent;
};

