#include "Delay.h"

#include <windows.h> // for Sleep

#include "Constants.h"

void Delay::delay()
{
    Sleep(SLEEP_MS);
}