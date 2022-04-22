#include "console-framework/View.h"
#include "console-framework/Map.h"
#include "console-framework/Console.h"

#define VIEW_PLAYER_OFFSET_X 10
#define VIEW_PLAYER_OFFSET_Y 6

View::View()
{
    COORD screen_size = Console::current().GetScreenSize();
    w = screen_size.X - 20;
    h = screen_size.Y - 3;

    offset_x = 0;
    offset_y = 0;

    Console::current().SetTextColor(CC_COLOR(CC_WHITE, CC_BLACK));

    for (int i = 0; i <= w; i++) {
        Console::current().SetCursorPos(i, h);
        putwchar(L'_');
    }
    for (int i = 0; i <= h; i++) {
        Console::current().SetCursorPos(w, i);
        putwchar(L'|');
    }

    Console::current().SetCursorPos(0, 0);
}

void View::Clear() const
{
    int view_w = w;
    int view_h = h;
    for (int x = 0; x < view_w; x++) {
        for (int y = 0; y < view_h; y++) {
            Console::current().SetCursorPos(x, y);
            putwchar(L' ');
        }
    }
}

bool View::CalculatePlayerOffset(const Map& map)
{
    int px = 0;
    int py = 0;
    int view_w = w;
    int view_h = h;
    bool changed = false;

    /* left */
    if (px < (offset_x + VIEW_PLAYER_OFFSET_X)) {
        if (px - VIEW_PLAYER_OFFSET_X > 0) {
            offset_x -= VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* right */
    if ((px - offset_x) > (view_w - VIEW_PLAYER_OFFSET_X)) {
        if (px + VIEW_PLAYER_OFFSET_X < map.GetSizeW()) {
            offset_x += VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* up */
    if (py < (offset_y + VIEW_PLAYER_OFFSET_Y)) {
        if (py - VIEW_PLAYER_OFFSET_Y > 0) {
            offset_y -= VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    /* down */
    if ((py - offset_y) > (view_h - VIEW_PLAYER_OFFSET_Y)) {
        if (py + VIEW_PLAYER_OFFSET_Y < map.GetSizeH()) {
            offset_y += VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    return changed;
}
