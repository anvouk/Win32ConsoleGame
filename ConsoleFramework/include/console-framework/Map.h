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
        assert(x < m_sizeW);
        assert(y < m_sizeH);
        return m_tiles[y * m_sizeW + x].get();
    }

    void ClearDirtyTiles();
    void PushDirtyTile(Tile* tile);

    void Draw(const View& view, const Player& player) const;
    void DrawDelta(const View& view);

    [[nodiscard]] int GetSizeW() const { return m_sizeW; }
    [[nodiscard]] int GetSizeH() const { return m_sizeH; }

private:
    const int m_sizeW, m_sizeH;
    std::unique_ptr<Tile>* m_tiles;
    std::queue<Tile*> m_dirtyTiles;
};
