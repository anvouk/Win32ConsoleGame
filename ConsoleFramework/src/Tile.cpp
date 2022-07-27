#include "console-framework/Tile.h"

Tile::Tile(int x, int y, WCHAR ch, CColor color, TileType type)
    : m_x(x)
    , m_y(y)
    , m_ch(ch)
    , m_color(color)
    , m_type(type)
{}

void Tile::UpdateCh(WCHAR newCh)
{
    m_ch = newCh;
}

void Tile::UpdateColor(CColor newColor)
{
    m_color = newColor;
}
