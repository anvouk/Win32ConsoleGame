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

    [[nodiscard]] Tile* GetCurrentTile() const { return currentTile; }

private:
    WCHAR ch;
    CColor color;

    // TODO: find better way to handle this
    WCHAR prevTileCh;
    CColor prevTileColor;

    Tile* currentTile;
};
