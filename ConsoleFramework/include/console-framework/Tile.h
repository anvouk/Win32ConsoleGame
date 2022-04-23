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
    explicit Tile(int x, int y, WCHAR ch, CColor color, TileType type);

    [[nodiscard]] int GetX() const { return x; }
    [[nodiscard]] int GetY() const { return y; }

    [[nodiscard]] WCHAR GetCh() const { return ch; }
    [[nodiscard]] CColor GetColor() const { return color; }
    [[nodiscard]] TileType GetTileType() const { return type; }

    void UpdateCh(WCHAR newCh);
    void UpdateColor(CColor newColor);

private:
    const int x, y;
    WCHAR ch;
    CColor color;
    TileType type;
};
