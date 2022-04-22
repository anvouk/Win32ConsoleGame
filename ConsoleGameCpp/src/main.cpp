#include "console-framework/Console.h"

#include "Map.h"
#include "View.h"

#include "Maps.inl"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main(int argc, const char* argv)
{
    auto file_logger = spdlog::basic_logger_mt("logger", "C:\\Users\\Andrew\\Documents\\RiderProjects\\ConsoleGameCpp\\x64\\Debug\\logs.log");
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::trace);

    spdlog::info("starting app");
    Console console = Console::current();

    const auto view = View();
    view.Clear();

    const auto& map = Map::CreateMap(level_1);
    map->Draw(view);

    spdlog::info("closing app");
    return 0;
}
