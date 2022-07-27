#include "console-framework/Player.h"

#include "console-framework/Tile.h"
#include "console-framework/Map.h"
#include "console-framework/View.h"

#include <fmt/format.h>

Player::Player(Tile* onTile)
    : m_ch(L'@')
    , m_color(CC_COLOR(CC_GREEN, CC_BLACK))
    , m_prevTileCh(L' ')
    , m_prevTileColor(CC_DEFAULT)
    , m_currentTile(onTile)
{}

bool Player::Move(Map& map, View& view, Tile* nextTile)
{
    if (nextTile->GetTileType() == TileType::Impassable) {
        return false;
    }

    // restore previous tile
    m_currentTile->UpdateCh(m_prevTileCh);
    m_currentTile->UpdateColor(m_prevTileColor);
    map.PushDirtyTile(m_currentTile);

    // backup new tile data
    m_prevTileCh = nextTile->GetCh();
    m_prevTileColor = nextTile->GetColor();

    // move to the new tile
    m_currentTile = nextTile;
    m_currentTile->UpdateCh(m_ch);
    m_currentTile->UpdateColor(m_color);
    map.PushDirtyTile(m_currentTile);

    DebugShowPos(view);
    if (view.CalculatePlayerOffset(map, *this)) {
        map.ClearDirtyTiles();
        map.Draw(view, *this);
    }

    return true;
}

void Player::DebugShowPos(const View& view) const
{
    WCHAR str[128];
    swprintf(
        str,
        128,
        L"Player tile(x: %d, y: %d)(offset: (%d, %d))      ",
        m_currentTile->GetX(),
        m_currentTile->GetY(),
        view.GetOffsetX(),
        view.GetOffsetY()
    );
    const auto& [_, h] = Console::current().GetScreenSize();
    Console::current().WriteStr(str, 0, h);
}
