#pragma once

#include "Win32.h"

struct PADDED_STR {
    /* http://www.fileformat.info/info/charset/UTF-16/list.htm */
    /* ▓ */
    WCHAR* ch;
    size_t length;
    WCHAR* begin;
    WCHAR* end;
    DWORD sleep_time;
};

typedef WORD CColor;

enum {
    CC_BLACK = 0,
    CC_DARKBLUE = FOREGROUND_BLUE,
    CC_DARKGREEN = FOREGROUND_GREEN,
    CC_DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
    CC_DARKRED = FOREGROUND_RED,
    CC_DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
    CC_DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
    CC_DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    CC_GRAY = FOREGROUND_INTENSITY,
    CC_BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    CC_GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CC_CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    CC_RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
    CC_MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    CC_YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    CC_WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    CC_COUNT
};

#define CC_COLOR(f, b) (((b) << 4) | (f))

#define CC_DEFAULT CC_COLOR(CC_WHITE, CC_BLACK)

class Console final {
    Console();
public:
    ~Console();

    static Console& current();

    void SetTextColor(CColor color) const;

    [[nodiscard]] COORD GetScreenSize() const;
    // TODO: Make work
    void SetScreenSize(int width, int height) const;

    void FillScreen(WCHAR ch) const;
    void WriteStr(const WCHAR* str, int posX, int posY) const;

    void ShowCursor(bool show = true) const;
    [[nodiscard]] COORD GetCursorPos() const;
    void SetCursorPos(int posX, int posY) const;

    /**
     * Write a string which simulates a loading bar.
     *
     * @param padStr		contains informations about the string to write
     * @param newline		should put a '\n' character at the end?
     * @param breakAt		if non-zero the loading bar will stop after this
     *						character count
     */
    void WritePaddedStr(const PADDED_STR* padStr, BOOL newline, int breakAt) const;

private:
    HANDLE consoleHandle;
};
