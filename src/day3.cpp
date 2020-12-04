#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>
#include <absl/strings/str_split.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "input.h"

ABSL_FLAG(bool, verbose, false, "Be more verbose");
ABSL_FLAG(bool, debug, false, "Be very verbose");
ABSL_FLAG(std::string, input, "", "Input data");

struct coordinate_t
{
    coordinate_t(int x, int y) : _x(x), _y(y) {}
    int _x;
    int _y;
};

// returns true if tree
bool lookup_map(std::vector<std::string> const &map_rows, coordinate_t const &pos)
{
    int width = map_rows[0].size();
    spdlog::debug("Map has width {}", width);
    int x = pos._x % width;

    auto c = map_rows[pos._y][x];

    return c == '#';
}

int get_tree_hits(std::vector<std::string> const &map_rows, int slope_x, int slope_y)
{
    int dx = slope_x;
    int dy = slope_y;

    coordinate_t pos(0, 0);

    int hits = 0;
    while (pos._y < map_rows.size())
    {
        if (lookup_map(map_rows, pos))
        {
            spdlog::info("hit tree on pos ({}, {})\n", pos._x, pos._y);
            hits++;
        }

        pos._x += dx;
        pos._y += dy;
    }

    return hits;
}

void part1(std::vector<std::string> const &map_rows)
{
    spdlog::info("Part 1");

    fmt::print("Hit a total of {} trees\n", get_tree_hits(map_rows, 3, 1));
}

void part2(std::vector<std::string> const &map_rows)
{
    spdlog::info("Part 2");

    int hits11 = get_tree_hits(map_rows, 1, 1);
    int hits31 = get_tree_hits(map_rows, 3, 1);
    int hits51 = get_tree_hits(map_rows, 5, 1);
    int hits71 = get_tree_hits(map_rows, 7, 1);
    int hits12 = get_tree_hits(map_rows, 1, 2);

    fmt::print("hits 1:1={}\n", hits11);
    fmt::print("hits 3:1={}\n", hits31);
    fmt::print("hits 5:1={}\n", hits51);
    fmt::print("hits 7:1={}\n", hits71);
    fmt::print("hits 1:2={}\n", hits12);

    fmt::print("product is: {}\n", hits11 * hits31 * hits51 * hits71 * hits12);
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 3");
    absl::ParseCommandLine(argc, argv);

    if (absl::GetFlag(FLAGS_debug))
    {
        spdlog::set_level(spdlog::level::debug);
    }
    else if (absl::GetFlag(FLAGS_verbose))
    {
        spdlog::set_level(spdlog::level::info);
    }
    else
    {
        spdlog::set_level(spdlog::level::warn);
    }

    std::vector<std::string> input_strings;
    spdlog::info("Parsing input");
    std::string input_path = absl::GetFlag(FLAGS_input);
    if (input_path.size() > 0)
    {
        input::get_file_input(input_path, input_strings);
    }
    else
    {
        input::get_stdin_input(input_strings);
    }

    part1(input_strings);
    part2(input_strings);

    return 0;
}