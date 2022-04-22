#include "Tile.h"

Tile::Tile(WCHAR ch, CColor color, TileType type)
    : ch(ch)
    , color(color)
    , type(type)
{}

std::unique_ptr<Tile> Tile::Create(WCHAR ch, CColor color, TileType type)
{
    return std::make_unique<Tile>(ch, color, type);
}

std::unique_ptr<Tile> Tile::CreateFloor(WCHAR ch, CColor color)
{
    return Create(ch, color, TileType::Floor);
}
