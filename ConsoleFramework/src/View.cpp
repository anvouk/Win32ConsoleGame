#include "console-framework/View.h"

#include "console-framework/Player.h"
#include "console-framework/Map.h"
#include "console-framework/Console.h"

#define VIEW_PLAYER_OFFSET_X 10
#define VIEW_PLAYER_OFFSET_Y 6

View::View()
{
    COORD screenSize = Console::current().GetScreenSize();
    m_w = screenSize.X - 20;
    m_h = screenSize.Y - 3;

    m_offsetX = 0;
    m_offsetY = 0;

    Console::current().SetTextColor(CC_COLOR(CC_WHITE, CC_BLACK));

    for (int i = 0; i <= m_w; i++) {
        Console::current().SetCursorPos(i, m_h);
        putwchar(L'_');
    }
    for (int i = 0; i <= m_h; i++) {
        Console::current().SetCursorPos(m_w, i);
        putwchar(L'|');
    }

    Console::current().SetCursorPos(0, 0);
}

void View::Clear() const
{
    const int viewW = m_w;
    const int viewH = m_h;
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
    const int viewW = m_w;
    const int viewH = m_h;
    bool changed = false;

    /* left */
    if (px < (m_offsetX + VIEW_PLAYER_OFFSET_X)) {
        if (px - VIEW_PLAYER_OFFSET_X > 0) {
            m_offsetX -= VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* right */
    if ((px - m_offsetX) > (viewW - VIEW_PLAYER_OFFSET_X)) {
        if (px + VIEW_PLAYER_OFFSET_X < map.GetSizeW()) {
            m_offsetX += VIEW_PLAYER_OFFSET_X;
            changed = true;
        }
    }

    /* up */
    if (py < (m_offsetY + VIEW_PLAYER_OFFSET_Y)) {
        if (py - VIEW_PLAYER_OFFSET_Y > 0) {
            m_offsetY -= VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    /* down */
    if ((py - m_offsetY) > (viewH - VIEW_PLAYER_OFFSET_Y)) {
        if (py + VIEW_PLAYER_OFFSET_Y < map.GetSizeH()) {
            m_offsetY += VIEW_PLAYER_OFFSET_Y;
            changed = true;
        }
    }

    return changed;
}
