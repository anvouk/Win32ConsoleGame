#include "console-framework/Player.h"

#include "console-framework/Tile.h"
#include "console-framework/Map.h"
#include "console-framework/View.h"

#include <fmt/format.h>

Player::Player(Tile* onTile)
    : ch(L'@')
    , color(CC_COLOR(CC_GREEN, CC_BLACK))
    , prevTileCh(L' ')
    , prevTileColor(CC_DEFAULT)
    , currentTile(onTile)
{}

bool Player::Move(Map& map, View& view, Tile* nextTile)
{
    if (nextTile->GetTileType() == TileType::Impassable) {
        return false;
    }

    // restore previous tile
    currentTile->UpdateCh(prevTileCh);
    currentTile->UpdateColor(prevTileColor);
    map.PushDirtyTile(currentTile);

    // backup new tile data
    prevTileCh = nextTile->GetCh();
    prevTileColor = nextTile->GetColor();

    // move to the new tile
    currentTile = nextTile;
    currentTile->UpdateCh(ch);
    currentTile->UpdateColor(color);
    map.PushDirtyTile(currentTile);

    DebugShowPos(view);
    if (view.CalculatePlayerOffset(map, *this)) {
        map.ClearDirtyTiles();
        map.Draw(view);
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
        currentTile->GetX(),
        currentTile->GetY(),
        view.GetOffsetX(),
        view.GetOffsetY()
    );
    const auto& [_, h] = Console::current().GetScreenSize();
    Console::current().WriteStr(str, 0, h);
}
