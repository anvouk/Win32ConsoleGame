#pragma once

#include "Tile.h"

#include <cassert>
#include <memory>

class View;

class Map final {
public:
    explicit Map(int size_w, int size_h, std::unique_ptr<Tile>* tiles);
    ~Map();

    static std::unique_ptr<Map> CreateMap(const WCHAR* rawData);

    FORCEINLINE const std::unique_ptr<Tile>& GetTile(int x, int y)
    {
        assert(x < size_w);
        assert(y < size_h);
        return tiles[y * size_w + x];
    }

    void Draw(const View& view);

    [[nodiscard]] int GetSizeW() const { return size_w; }
    [[nodiscard]] int GetSizeH() const { return size_h; }

private:
    const int size_w, size_h;
    std::unique_ptr<Tile>* tiles;
};
