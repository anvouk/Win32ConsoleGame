#pragma once

#include "console-framework/Console.h"
#include <memory>

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

    static std::unique_ptr<Tile> Create(WCHAR ch, CColor color, TileType type);
    static std::unique_ptr<Tile> CreateFloor(WCHAR ch, CColor color);

    [[nodiscard]] WCHAR GetCh() const { return ch; }
    [[nodiscard]] CColor GetColor() const { return color; }
    [[nodiscard]] TileType GetTileType() const { return type; }

private:
    WCHAR ch;
    CColor color;
    TileType type;
};
