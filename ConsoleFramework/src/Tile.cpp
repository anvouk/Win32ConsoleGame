#include "console-framework/Tile.h"

Tile::Tile(int x, int y, WCHAR ch, CColor color, TileType type)
    : x(x)
    , y(y)
    , ch(ch)
    , color(color)
    , type(type)
{}

void Tile::UpdateCh(WCHAR newCh)
{
    ch = newCh;
}

void Tile::UpdateColor(CColor newColor)
{
    color = newColor;
}
