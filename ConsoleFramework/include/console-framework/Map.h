#pragma once

#include "Tile.h"

#include <cassert>
#include <memory>
#include <queue>

class Player;
class View;

class Map final {
public:
    explicit Map(int size_w, int size_h, std::unique_ptr<Tile>* tiles);
    ~Map();

    static std::tuple<std::unique_ptr<Map>, std::unique_ptr<Player>> CreateMap(const WCHAR* rawData);

    FORCEINLINE Tile* GetTile(int x, int y) const
    {
        assert(x < size_w);
        assert(y < size_h);
        return tiles[y * size_w + x].get();
    }

    void ClearDirtyTiles();
    void PushDirtyTile(Tile* tile);

    void Draw(const View& view, const Player& player) const;
    void DrawDelta(const View& view);

    [[nodiscard]] int GetSizeW() const { return size_w; }
    [[nodiscard]] int GetSizeH() const { return size_h; }

private:
    const int size_w, size_h;
    std::unique_ptr<Tile>* tiles;
    std::queue<Tile*> dirtyTiles;
};
