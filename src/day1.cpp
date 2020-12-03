#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "input.h"

ABSL_FLAG(bool, verbose, false, "Be more verbose");
ABSL_FLAG(bool, debug, false, "Be very verbose");
ABSL_FLAG(std::string, input, "", "Input data");

using int_t = uint32_t;

void part1(std::unordered_set<int_t> const &data)
{
    for (auto d : data)
    {
        if (data.count(2020 - d))
        {
            fmt::print("Found matching set: {}, {}\n", d, 2020-d);
            fmt::print("Product is {}\n", d *(2020-d));
        }
    }
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 1");
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

    std::vector<std::string> args(argv, argv + argc);

    std::vector<int_t> input;

    std::transform(input_strings.begin(), input_strings.end(), std::back_inserter(input),
                   [](std::string s) -> int_t { return std::stol(s); });

    std::unordered_set<int_t> data(std::begin(input), std::end(input));

    part1(data);

    return 0;
}