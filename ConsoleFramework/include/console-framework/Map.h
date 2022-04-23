#pragma once

#include "Tile.h"

#include <cassert>
#include <memory>
#include <queue>

class Player;
class View;

class Map final {
public:
    explicit Map(int sizeW, int sizeH, std::unique_ptr<Tile>* tiles);
    ~Map();

    static std::tuple<std::unique_ptr<Map>, std::unique_ptr<Player>> CreateMap(const WCHAR* rawData);

    FORCEINLINE Tile* GetTile(int x, int y) const
    {
        assert(x < sizeW);
        assert(y < sizeH);
        return tiles[y * sizeW + x].get();
    }

    void ClearDirtyTiles();
    void PushDirtyTile(Tile* tile);

    void Draw(const View& view, const Player& player) const;
    void DrawDelta(const View& view);

    [[nodiscard]] int GetSizeW() const { return sizeW; }
    [[nodiscard]] int GetSizeH() const { return sizeH; }

private:
    const int sizeW, sizeH;
    std::unique_ptr<Tile>* tiles;
    std::queue<Tile*> dirtyTiles;
};
