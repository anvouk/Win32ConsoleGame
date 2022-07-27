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
    static constexpr int GAME_FPS = 30;
    static constexpr int GAME_TICKS_PER_FRAME = 1000 / GAME_FPS;

    LARGE_INTEGER firstTick;
    LARGE_INTEGER ticksPerSecond;

    uint64_t startTicks = 0;
};
