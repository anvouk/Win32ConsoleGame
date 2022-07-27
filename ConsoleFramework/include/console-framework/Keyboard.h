#pragma once

#include "Win32.h"

enum class KeyboardKeyCodes {
    key_0 = 0x30,
    key_1 = 0x31,
    key_2 = 0x32,
    key_3 = 0x33,
    key_4 = 0x34,
    key_5 = 0x35,
    key_6 = 0x36,
    key_7 = 0x37,
    key_8 = 0x38,
    key_9 = 0x39,
    key_A = 0x41,
    key_B = 0x42,
    key_C = 0x43,
    key_D = 0x44,
    key_E = 0x45,
    key_F = 0x46,
    key_G = 0x47,
    key_H = 0x48,
    key_I = 0x49,
    key_J = 0x4A,
    key_K = 0x4B,
    key_L = 0x4C,
    key_M = 0x4D,
    key_N = 0x4E,
    key_O = 0x4F,
    key_P = 0x50,
    key_Q = 0x51,
    key_R = 0x52,
    key_S = 0x53,
    key_T = 0x54,
    key_U = 0x55,
    key_V = 0x56,
    key_W = 0x57,
    key_X = 0x58,
    key_Y = 0x59,
    key_Z = 0x5A,
};

/**
 * Check if the key is currently being pressed.
 * @param keycode the virtual key code
 * @return 1 if it's pressed
 */
FORCEINLINE int KeyIsDown(int keycode)
{
    return GetAsyncKeyState(keycode);
}

/**
 * Check if the key state has changed.
 * @param keycode the virtual key code
 * @return 1 if the key state changed to pressed
 */
FORCEINLINE int KeyIsPressed(int keycode)
{
    return (GetAsyncKeyState(keycode) & 0x1);
}
