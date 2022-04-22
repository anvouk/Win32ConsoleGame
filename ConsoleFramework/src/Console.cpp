#include "console-framework/Console.h"

#include <cstdio>
#include <cassert>
#include <fcntl.h>
#include <io.h>

static void SetLucidaFont(HANDLE conHandle)
{
    CONSOLE_FONT_INFOEX info;
    memset(&info, 0, sizeof(CONSOLE_FONT_INFOEX));
    info.cbSize = sizeof(CONSOLE_FONT_INFOEX); // prevents err=87 below
    if (GetCurrentConsoleFontEx(conHandle, FALSE, &info)) {
        info.FontFamily = FF_DONTCARE;
        info.dwFontSize.X = 0; // leave X as zero
        info.dwFontSize.Y = 14;
        info.FontWeight = 400;
        wcscpy_s(info.FaceName, LF_FACESIZE, L"Lucida Console");
        SetCurrentConsoleFontEx(conHandle, FALSE, &info);
    }
}

Console::Console()
{
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // enable UTF-8 in console
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    SetLucidaFont(consoleHandle);

    // does really do anything?
    // SetConsoleOutputCP( 65001 );
}

Console::~Console()
{
    ShowCursor();

    // use normal widows ascii for console
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stderr), _O_TEXT);

    CloseHandle(consoleHandle);
}

Console& Console::current()
{
    static Console console;
    return console;
}

void Console::SetTextColor(CColor color) const
{
    SetConsoleTextAttribute(consoleHandle, color);
}

COORD Console::GetScreenSize() const
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(consoleHandle, &info);
    return{info.srWindow.Right, info.srWindow.Bottom};
}

void Console::SetScreenSize(int width, int height) const
{
    assert(width > 0);
    assert(height > 0);

    COORD coord;
    coord.X = width;
    coord.Y = height;

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = height - 1;
    rect.Right = width - 1;

    SetConsoleScreenBufferSize(consoleHandle, coord);

    /* Set the window size to that specified in Rect */
    BOOL val = SetConsoleWindowInfo(consoleHandle, 1, &rect);
}

void Console::FillScreen(WCHAR ch) const
{
    LPDWORD b = NULL;
    COORD size = GetScreenSize();
    COORD a;
    a.X = 0;
    for (int i = 0; i < size.Y; i++) {
        a.Y = i;
        FillConsoleOutputCharacterW(consoleHandle, ch, size.X, a, b);
    }
}

void Console::WriteStr(const WCHAR* str, SHORT posX, SHORT posY) const
{
    DWORD n;
    WriteConsoleOutputCharacterW(consoleHandle, str, wcslen(str), {posX, posY}, &n);
}

void Console::ShowCursor(bool show) const
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 10;
    info.bVisible = show;
    SetConsoleCursorInfo(consoleHandle, &info);
}

COORD Console::GetCursorPos() const
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(consoleHandle, &info);
    return info.dwCursorPosition;
}

void Console::SetCursorPos(SHORT posX, SHORT posY) const
{
    SetConsoleCursorPosition(consoleHandle, {posX, posY});
}

// FIXME: ingoring current console color
void Console::WritePaddedStr(const PADDED_STR* padStr, BOOL newline, int breakAt) const
{
    WCHAR str[128] = L"";
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(consoleHandle, &info);
    COORD pos;
    pos.X = wcslen(padStr->begin);
    pos.Y = info.dwCursorPosition.Y;
    WriteStr(padStr->begin, info.dwCursorPosition.X, info.dwCursorPosition.Y);
    WriteStr(padStr->end, pos.X + (SHORT)padStr->length, info.dwCursorPosition.Y);
    for (size_t i = 0; i < padStr->length; i++) {
        Sleep(padStr->sleep_time);
        if (i == breakAt && breakAt != 0) {
            break;
        }
        wcscat_s(str, 128, padStr->ch);
        WriteStr(str, pos.X, pos.Y);
    }
    if (newline) {
        pos.X = info.dwCursorPosition.X;
        pos.Y++;
        SetConsoleCursorPosition(consoleHandle, pos);
    } else {
        pos.X += (SHORT)padStr->length + wcslen(padStr->end);
        SetConsoleCursorPosition(consoleHandle, pos);
    }
}
