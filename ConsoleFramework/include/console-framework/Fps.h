#pragma once

#include "Win32.h"

#include <cstdint>

// inspired from SLD2 SDL_GetTicks64().
// see https://github.com/libsdl-org/SDL/blob/dbf79405416400cfeecc4b1d92eeda24421edd5f/src/timer/windows/SDL_systimer.c#L114
class Fps final {
public:
    Fps();

    [[nodiscard]] uint64_t GetTicks() const;

    void BeginFpsCap();
    void EndFpsCap() const;

private:
    static constexpr int s_gameFps = 30;
    static constexpr int s_gameTicksPerFrame = 1000 / s_gameFps;

    LARGE_INTEGER m_firstTick;
    LARGE_INTEGER m_ticksPerSecond;

    uint64_t m_startTicks = 0;
};
