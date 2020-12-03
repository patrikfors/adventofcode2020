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

struct policy_t
{
    int min;
    int max;
    char character;
};

struct input_t
{
    policy_t policy;
    std::string password;
};

void part1(std::vector<input_t> const &data)
{
    int valids = 0;
    for (auto d : data)
    {
        int count = 0;
        for (auto c : d.password)
        {
            if (c == d.policy.character)
            {
                count++;
            }
        }

        if (count < d.policy.min)
        {
            spdlog::info("Rejecting {}, less than {} of '{}'\n", d.password, d.policy.min, d.policy.character);
        }
        else if (count > d.policy.max)
        {
            spdlog::info("Rejecting {}, more than {} of '{}'\n", d.password, d.policy.max, d.policy.character);
        }
        else
        {
            valids++;
        }
    }

    fmt::print("{} valid passwords.\n", valids);
}

void part2(std::vector<input_t> const &data)
{
    int valids = 0;
    for (auto d : data)
    {
        int count = 0;
        count += (d.password[d.policy.min - 1] == d.policy.character);
        count += (d.password[d.policy.max - 1] == d.policy.character);

        if (count == 0)
        {

            spdlog::info("Rejecting {}, neither position {} or {} is {}\n", d.password, d.policy.min, d.policy.max, d.policy.character);
        }
        else if (count == 2)
        {
            spdlog::info("Rejecting {}, both position {} and {} is {}\n", d.password, d.policy.min, d.policy.max, d.policy.character);
        }
        else
        {
            valids++;
        }
    }

    fmt::print("{} valid passwords.\n", valids);
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 2");
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

    std::vector<input_t> input;

    std::transform(input_strings.begin(), input_strings.end(), std::back_inserter(input),
                   [](std::string s) -> input_t {
                       // better have good input, no error checking here..

                       //1-3 a: abcde
                       input_t rval;

                       std::vector<std::string> v1 = absl::StrSplit(s, '-');
                       rval.policy.min = std::stoi(v1[0]);

                       std::vector<std::string> v2 = absl::StrSplit(v1[1], ' ');
                       rval.policy.max = std::stoi(v2[0]);

                       std::vector<std::string> v3 = absl::StrSplit(v2[1], ':');
                       rval.policy.character = v3[0][0];

                       rval.password = v2[2];

                       spdlog::debug("Converted \"{}\" to {}-{} {}: {}\n",
                                     s,
                                     rval.policy.min,
                                     rval.policy.max,
                                     rval.policy.character,
                                     rval.password);

                       return rval;
                   });

    // std::unordered_set<int_t> data(std::begin(input), std::end(input));

    part1(input);
    part2(input);

    return 0;
}