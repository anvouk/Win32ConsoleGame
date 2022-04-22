#pragma once

#include "console-framework/Console.h"

enum class TileType {
    Floor,
    Impassable,
    Pickup,
    Enemy,
    GateExit,
    Player,
};

class Tile {
public:
    explicit Tile(WCHAR ch, CColor color, TileType type);

    [[nodiscard]] WCHAR GetCh() const { return ch; }
    [[nodiscard]] CColor GetColor() const { return color; }
    [[nodiscard]] TileType GetTileType() const { return type; }

private:
    WCHAR ch;
    CColor color;
    TileType type;
};
