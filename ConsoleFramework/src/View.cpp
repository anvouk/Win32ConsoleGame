#include "console-framework/View.h"

#include "console-framework/Player.h"
#include "console-framework/Map.h"
#include "console-framework/Console.h"

#define VIEW_PLAYER_OFFSET_X 10
#define VIEW_PLAYER_OFFSET_Y 6

View::View()
{
    COORD screenSize = Console::current().GetScreenSize();
    w = screenSize.X - 20;
    h = screenSize.Y - 3;

    offsetX = 0;
    offsetY = 0;

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
    int viewW = w;
    int viewH = h;
    for (int x = 0; x < viewW; x++) {
        for (int y = 0; y < viewH; y++) {
            Console::current().SetCursorPos(x, y);
            putwchar(L' ');
        }
    }
}

bool View::CalculatePlayerOffset(const Map& map, const Player& player)
{
    const int px = player.GetCurrentTile()->GetX();
    const int py = player.GetCurrentTile()->GetY();
    const int viewW = w;
    const int viewH = h;
    bool changed = false;

    /* left */
    if (px < (offsetX + VIEW_PLAYER_OFFSET_X)) {
        if (px - VIEW_PLAYER_OFFSET_X > 0) {
            offsetX -= VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* right */
    if ((px - offsetX) > (viewW - VIEW_PLAYER_OFFSET_X)) {
        if (px + VIEW_PLAYER_OFFSET_X < map.GetSizeW()) {
            offsetX += VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* up */
    if (py < (offsetY + VIEW_PLAYER_OFFSET_Y)) {
        if (py - VIEW_PLAYER_OFFSET_Y > 0) {
            offsetY -= VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    /* down */
    if ((py - offsetY) > (viewH - VIEW_PLAYER_OFFSET_Y)) {
        if (py + VIEW_PLAYER_OFFSET_Y < map.GetSizeH()) {
            offsetY += VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    return changed;
}
