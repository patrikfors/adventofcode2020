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
    boarding_pass_t(int row, int col) : _row(row), _col(col)
    {
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

void part1(std::vector<std::vector<std::string>> groups)
{
    spdlog::info("Part 1");

    std::vector<int> group_answers;

    for (auto g : groups)
    {
        std::set<char> questions;
        for (auto s : g)
        {
            for (char c : s)
            {
                questions.emplace(c);
            }
        }

        group_answers.emplace_back(questions.size());
        spdlog::info("{}", questions.size());
    }

    int sum = 0;
    for (int a : group_answers)
    {
        sum += a;
    }

    fmt::print("sum = {}\n", sum);
}

void part2(std::vector<std::vector<std::string>> groups)
{
    spdlog::info("Part 2");

    std::vector<int> group_answers;

    for (auto g : groups)
    {
        std::set<char> all_yes_questions; // all questions the groups has yes'ed

        bool first = true; // keep track of first person because there we shouldnt intersect
        for (auto person : g)
        {
            std::set<char> questions; // the questions for this person
            for (char c : person)
            {
                questions.emplace(c);
            }

            if (first)
            {
                all_yes_questions = questions;
            }
            else
            {
                std::set<char> new_all_yes;
                set_intersection(questions.begin(), questions.end(), all_yes_questions.begin(), all_yes_questions.end(), std::inserter(new_all_yes, new_all_yes.begin()));
                all_yes_questions = new_all_yes;
            }

            first = false;
        }

        group_answers.emplace_back(all_yes_questions.size());
        spdlog::info("{}", all_yes_questions.size());
    }

    int sum = 0;
    for (int a : group_answers)
    {
        sum += a;
    }

    fmt::print("sum = {}\n", sum);
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 6");
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

    std::vector<std::vector<std::string>> groups;

    input::group_by_newline(input_strings, groups);

    int group_idx = 0;
    for (auto g : groups)
    {
        fmt::print("group {}\n", group_idx++);
        for (auto s : g)
        {
            fmt::print("\t{}\n", s);
        }
    }

    //part1(groups);
    part2(groups);

    return 0;
}