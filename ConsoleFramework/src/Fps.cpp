#include "console-framework/Fps.h"

Fps::Fps()
{
    QueryPerformanceFrequency(&m_ticksPerSecond);
    QueryPerformanceCounter(&m_firstTick);
}

uint64_t Fps::GetTicks() const
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return static_cast<uint64_t>(((now.QuadPart - m_firstTick.QuadPart) * 1000) / m_ticksPerSecond.QuadPart);
}

void Fps::BeginFpsCap()
{
    m_startTicks = GetTicks();
}

void Fps::EndFpsCap() const
{
    const uint64_t deltaTicks = GetTicks() - m_startTicks;
    if (deltaTicks < s_gameTicksPerFrame) {
        Sleep(s_gameTicksPerFrame - deltaTicks);
    }
}
