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

    [[nodiscard]] int GetX() const { return m_x; }
    [[nodiscard]] int GetY() const { return m_y; }

    [[nodiscard]] WCHAR GetCh() const { return m_ch; }
    [[nodiscard]] CColor GetColor() const { return m_color; }
    [[nodiscard]] TileType GetTileType() const { return m_type; }

    void UpdateCh(WCHAR newCh);
    void UpdateColor(CColor newColor);

private:
    const int m_x, m_y;
    WCHAR m_ch;
    CColor m_color;
    TileType m_type;
};
