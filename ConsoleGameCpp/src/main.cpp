#include "console-framework/Console.h"

#include "console-framework/Map.h"
#include "console-framework/View.h"

#include "Maps.inl"
#include "console-framework/Player.h"
#include "console-framework/Keyboard.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main(int argc, const char* argv)
{
    auto file_logger = spdlog::basic_logger_mt("logger", "logs.log");
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::trace);

    spdlog::info("starting app");
    Console console = Console::current();
    console.ShowCursor(false);

    View view = View();
    view.Clear();

    auto [map, player] = Map::CreateMap(level_1);
    if (!(map && player)) {
        return 1;
    }

    map->Draw(view, *player);

    while (true) {
        if (key_is_down(VK_ESCAPE)) {
            break;
        }

        // debug purposes only
        if (key_is_down(VK_F1)) {
            map->Draw(view, *player);
        }

        map->DrawDelta(view);

        // player inputs
        // TODO: cleanup
        if (key_is_down(VK_UP)) {
            int px = player->GetCurrentTile()->GetX();
            int py = player->GetCurrentTile()->GetY();
            int new_coord_val = py - 1;
            if (new_coord_val >= 0) {
                Console::current().SetCursorPos(px, new_coord_val);
                player->Move(*map, view, map->GetTile(px, new_coord_val));
            }
        } else if (key_is_down(VK_DOWN)) {
            int px = player->GetCurrentTile()->GetX();
            int py = player->GetCurrentTile()->GetY();
            int new_coord_val = py + 1;
            if (new_coord_val < map->GetSizeH()) {
                Console::current().SetCursorPos(px, new_coord_val);
                player->Move(*map, view, map->GetTile(px, new_coord_val));
            }
        } else if (key_is_down(VK_LEFT)) {
            int px = player->GetCurrentTile()->GetX();
            int py = player->GetCurrentTile()->GetY();
            int new_coord_val = px - 1;
            if (new_coord_val >= 0) {
                Console::current().SetCursorPos(new_coord_val, py);
                player->Move(*map, view, map->GetTile(new_coord_val, py));
            }
        } else if (key_is_down(VK_RIGHT)) {
            int px = player->GetCurrentTile()->GetX();
            int py = player->GetCurrentTile()->GetY();
            int new_coord_val = px + 1;
            if (new_coord_val < map->GetSizeW()) {
                Console::current().SetCursorPos(new_coord_val, py);
                player->Move(*map, view, map->GetTile(new_coord_val, py));
            }
        }

        Sleep(50);
    }

    spdlog::info("closing app");
    return 0;
}
