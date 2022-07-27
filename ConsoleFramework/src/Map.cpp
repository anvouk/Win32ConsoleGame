#include "console-framework/Map.h"

#include "console-framework/Player.h"
#include "console-framework/View.h"

#include <tuple>
#include <spdlog/spdlog.h>

static std::tuple<size_t, size_t> GetMapSize(const WCHAR* ch_map)
{
    size_t maxX = 0;
    size_t maxY = 0;

    size_t tmp_x = 0;
    for (const WCHAR* i = ch_map; *i != L'\0'; ++i) {
        if (*i == L'\n') {
            maxY++;
            tmp_x = 0;
        }
        if (*i == L'\t') {
            spdlog::warn("Found unwanted character '\\t' at ({}:{}) in the map", tmp_x, maxY);
        }
        tmp_x++;
        if (tmp_x > maxX) {
            maxX = tmp_x;
        }
    }

    return {
        maxX,
        maxY
    };
}

Map::Map(int sizeW, int sizeH, std::unique_ptr<Tile>* tiles)
    : m_sizeW(sizeW)
    , m_sizeH(sizeH)
    , m_tiles(tiles)
{}

Map::~Map()
{
    delete[] m_tiles;
}

std::tuple<std::unique_ptr<Map>, std::unique_ptr<Player>> Map::CreateMap(const WCHAR* rawData)
{
    spdlog::debug("Loading map");
    const auto [maxX, maxY] = GetMapSize(rawData);
    spdlog::debug("Map size (w: {}, h: {})", maxX, maxY);

    // std::unique_ptr<Tile>[y][x]
    const auto tiles = new std::unique_ptr<Tile>[maxX * maxY];

    std::unique_ptr<Player> player;

    for (size_t y = 0; y < maxY; ++y) {
        for (size_t x = 0; x < maxX; ++x) {
            const WCHAR ch = rawData[y * maxX + x];
            if (ch == L'\0')
                goto done;

            // TODO: use tile db
            switch (ch) {
                case L'@':
                    spdlog::debug("Player found ({}:{})", x, y);
                    tiles[y * maxX + x] = std::make_unique<Tile>(x, y, ch, CC_COLOR(CC_GREEN, CC_BLACK), TileType::Player);
                    player = std::make_unique<Player>(tiles[y * maxX + x].get());
                    continue;
                case L'\u2588':
                    tiles[y * maxX + x] = std::make_unique<Tile>(x, y, ch, CC_COLOR(CC_RED, CC_BLACK), TileType::Impassable);
                    continue;
                default:
                    tiles[y * maxX + x] = std::make_unique<Tile>(x, y, ch, CC_DEFAULT, TileType::Floor);
                    continue;
            }
        }
    }
    done:

    if (!player) {
        spdlog::error("Player not found on map");
        return std::make_tuple(nullptr, nullptr);
    }

    spdlog::debug("Map loaded successfully");
    return std::make_tuple(std::make_unique<Map>(maxX, maxY, tiles), std::forward<std::unique_ptr<Player>>(player));
}

void Map::ClearDirtyTiles()
{
    while (!m_dirtyTiles.empty()) {
        m_dirtyTiles.pop();
    }
}

void Map::PushDirtyTile(Tile* tile)
{
    m_dirtyTiles.push(tile);
}

void Map::Draw(const View& view, const Player& player) const
{
    const int view_w = view.GetWidth();
    const int view_h = view.GetHeight();

    const int offset_x = view.GetOffsetX();
    const int offset_y = view.GetOffsetY();

    view.Clear();

    for (int y = 0, ty = offset_y; y < view_h && ty < m_sizeH; y++, ty++) {
        for (int x = 0, tx = offset_x; x < view_w && tx < m_sizeW; x++, tx++) {
            const auto& t = GetTile(tx, ty);
            Console::current().SetTextColor(t->GetColor());
            // optimization: ConsoleWriteStr does not respect colors but it's faster
            // than just moving the cursor to print a character there.
            if (t->GetColor() != CC_DEFAULT) {
                Console::current().SetCursorPos(x, y);
                putwchar(t->GetCh());
            } else {
                Console::current().WriteStr(std::wstring(1, t->GetCh()).c_str(), x, y);
            }
        }
    }

    Console::current().SetTextColor(CC_DEFAULT);

    // set cursor to player
    Console::current().SetCursorPos(
        player.GetCurrentTile()->GetX(), player.GetCurrentTile()->GetY()
    );
}

void Map::DrawDelta(const View& view)
{
    while (!m_dirtyTiles.empty()) {
        const auto& t = m_dirtyTiles.front();
        m_dirtyTiles.pop();
        Console::current().SetTextColor(t->GetColor());
        Console::current().SetCursorPos(
            t->GetX() - view.GetOffsetX(),
            t->GetY() - view.GetOffsetY()
        );
        putwchar(t->GetCh());
    }
}
