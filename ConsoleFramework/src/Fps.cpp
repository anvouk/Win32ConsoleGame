#include "console-framework/Fps.h"

Fps::Fps()
{
    QueryPerformanceFrequency(&ticksPerSecond);
    QueryPerformanceCounter(&firstTick);
}

uint64_t Fps::GetTicks() const
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return static_cast<uint64_t>(((now.QuadPart - firstTick.QuadPart) * 1000) / ticksPerSecond.QuadPart);
}

void Fps::BeginFpsCap()
{
    startTicks = GetTicks();
}

void Fps::EndFpsCap() const
{
    const uint64_t deltaTicks = GetTicks() - startTicks;
    if (deltaTicks < GAME_TICKS_PER_FRAME) {
        Sleep(GAME_TICKS_PER_FRAME - deltaTicks);
    }
}
