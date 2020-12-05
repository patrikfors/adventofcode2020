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

struct boarding_pass_t
{
    boarding_pass_t(int row, int col) : _row(row), _col(col) {
        _id = row * 8 + col;
    }

    int _row;
    int _col;
    int _id;
};

template <typename OutputIterator>
OutputIterator parse_input(std::vector<std::string> const &raw_data, OutputIterator out)
{
    for (auto s : raw_data)
    {
        int row = 0;
        int col = 0;
        for (auto c : s)
        {
            if (c == 'F')
            {
                row <<= 1;
            }
            else if (c == 'B')
            {
                row <<= 1;
                row |= 1;
            }
            else if (c == 'R')
            {
                col <<= 1;
                col |= 1;
            }
            else if (c == 'L')
            {
                col <<= 1;
            }
        }
        *out++ = boarding_pass_t(row, col);
    }

    return out;
}

void part1(std::vector<boarding_pass_t> const &boarding_passes)
{
    spdlog::info("Part 1");

    // for (auto b : boarding_passes)
    // {
    //     fmt::print("{:03d}:{}\n", b._row, b._col);
    // }

    int largest = 0;
    for (auto b : boarding_passes) {
        if(b._id > largest) {
            largest = b._id;
        }
    }

    fmt::print("largest id: {}\n", largest);
}

void part2(std::vector<std::string> const &map_rows)
{
    spdlog::info("Part 2");
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 5");
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

    std::vector<boarding_pass_t> boarding_passes;
    parse_input(input_strings, std::back_inserter(boarding_passes));
    part1(boarding_passes);
    part2(input_strings);

    return 0;
}