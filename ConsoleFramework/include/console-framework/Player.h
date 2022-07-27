#pragma once
#include "Console.h"
#include "Win32.h"

class View;
class Tile;
class Map;

class Player final {
public:
    explicit Player(Tile* onTile);
    Player(const Player&) = delete;
    Player(Player&&) = delete;

    bool Move(Map& map, View& view, Tile* nextTile);

    void DebugShowPos(const View& view) const;

    [[nodiscard]] Tile* GetCurrentTile() const { return m_currentTile; }

private:
    WCHAR m_ch;
    CColor m_color;

    // TODO: find better way to handle this
    WCHAR m_prevTileCh;
    CColor m_prevTileColor;

    Tile* m_currentTile;
};
