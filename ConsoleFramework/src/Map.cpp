#include "console-framework/Map.h"

#include "console-framework/Player.h"
#include "console-framework/View.h"

#include <tuple>
#include <spdlog/spdlog.h>

static std::tuple<size_t, size_t> map_get_dimension(const WCHAR* ch_map)
{
    size_t max_x = 0;
    size_t max_y = 0;

    size_t tmp_x = 0;
    for (const WCHAR* i = ch_map; *i != L'\0'; ++i) {
        if (*i == L'\n') {
            max_y++;
            tmp_x = 0;
        }
        if (*i == L'\t') {
            spdlog::warn("Found unwanted character '\\t' at ({}:{}) in the map", tmp_x, max_y);
        }
        tmp_x++;
        if (tmp_x > max_x) {
            max_x = tmp_x;
        }
    }

    return {
        max_x,
        max_y
    };
}

Map::Map(int size_w, int size_h, std::unique_ptr<Tile>* tiles)
    : size_w(size_w)
    , size_h(size_h)
    , tiles(tiles)
{}

Map::~Map()
{
    delete[] tiles;
}

std::tuple<std::unique_ptr<Map>, std::unique_ptr<Player>> Map::CreateMap(const WCHAR* rawData)
{
    spdlog::debug("Loading map");
    const auto [max_x, max_y] = map_get_dimension(rawData);
    spdlog::debug("Map size (w: {}, h: {})", max_x, max_y);

    // std::unique_ptr<Tile>[y][x]
    const auto tiles = new std::unique_ptr<Tile>[max_x * max_y];

    std::unique_ptr<Player> player;

    for (size_t y = 0; y < max_y; ++y) {
        for (size_t x = 0; x < max_x; ++x) {
            const WCHAR ch = rawData[y * max_x + x];
            if (ch == L'\0')
                goto done;

            // TODO: use tile db
            switch (ch) {
                case L'@':
                    spdlog::debug("Player found ({}:{})", x, y);
                    tiles[y * max_x + x] = std::make_unique<Tile>(x, y, ch, CC_COLOR(CC_GREEN, CC_BLACK), TileType::Player);
                    player = std::make_unique<Player>(tiles[y * max_x + x].get());
                    continue;
                case L'\u2588':
                    tiles[y * max_x + x] = std::make_unique<Tile>(x, y, ch, CC_COLOR(CC_RED, CC_BLACK), TileType::Impassable);
                    continue;
                default:
                    tiles[y * max_x + x] = std::make_unique<Tile>(x, y, ch, CC_DEFAULT, TileType::Floor);
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
    return std::make_tuple(std::make_unique<Map>(max_x, max_y, tiles), std::forward<std::unique_ptr<Player>>(player));
}

void Map::ClearDirtyTiles()
{
    while (!dirtyTiles.empty()) {
        dirtyTiles.pop();
    }
}

void Map::PushDirtyTile(Tile* tile)
{
    dirtyTiles.push(tile);
}

void Map::Draw(const View& view, const Player& player) const
{
    const int view_w = view.GetWidth();
    const int view_h = view.GetHeight();

    const int offset_x = view.GetOffsetX();
    const int offset_y = view.GetOffsetY();

    view.Clear();

    for (int y = 0, ty = offset_y; y < view_h && ty < size_h; y++, ty++) {
        for (int x = 0, tx = offset_x; x < view_w && tx < size_w; x++, tx++) {
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
    while (!dirtyTiles.empty()) {
        const auto& t = dirtyTiles.front();
        dirtyTiles.pop();
        Console::current().SetTextColor(t->GetColor());
        Console::current().SetCursorPos(
            t->GetX() - view.GetOffsetX(),
            t->GetY() - view.GetOffsetY()
        );
        putwchar(t->GetCh());
    }
}
