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

std::map<std::string, size_t> required_fields = {
    {"byr", 0},
    {"iyr", 1},
    {"eyr", 2},
    {"hgt", 3},
    {"hcl", 4},
    {"ecl", 5},
    {"pid", 6}};

using field_t = uint32_t;

field_t get_fields(std::string const &s, bool strict = false)
{
    field_t rval = 0;

    spdlog::debug("Get fields '{}':", s);
    std::vector<std::string> nvs = absl::StrSplit(s, ' ');

    for (auto nv : nvs)
    {
        std::vector<std::string> words = absl::StrSplit(nv, ':');
        if (required_fields.count(words[0]))
        {
            bool ok = true;

            if (strict)
            {

                if (words[0] == "byr") // byr (Birth Year) - four digits; at least 1920 and at most 2002.
                {
                    auto byr = std::stoi(words[1]);

                    if (byr < 1920 || byr > 2002)
                    {
                        ok = false;
                    }
                }
                else if (words[0] == "iyr") // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
                {
                    auto iyr = std::stoi(words[1]);

                    if (iyr < 2010 || iyr > 2020)
                    {
                        ok = false;
                    }
                }
                else if (words[0] == "eyr") // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
                {
                    auto eyr = std::stoi(words[1]);

                    if (eyr < 2020 || eyr > 2030)
                    {
                        ok = false;
                    }
                }
                else if (words[0] == "hgt")
                // hgt (Height) - a number followed by either cm or in:
                // If cm, the number must be at least 150 and at most 193.
                // If in, the number must be at least 59 and at most 76.
                {
                    size_t pos = 0;
                    auto hgt = std::stoi(words[1], &pos);
                    std::string unit = words[1].substr(pos);
                    spdlog::debug("{} has unit {} (pos={})", nv, unit, pos);

                    if (unit == "cm")
                    {
                        if (hgt < 150 || hgt > 193)
                        {
                            ok = false;
                        }
                    }
                    else if (unit == "in")
                    {
                        if (hgt < 59 || hgt > 76)
                        {
                            ok = false;
                        }
                    }
                    else
                    {
                        ok = false;
                    }
                }
                else if (words[0] == "hcl") // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
                {
                    auto hcl = words[1];
                    if (hcl[0] != '#')
                    {
                        spdlog::info("color doesnt start with #");
                        ok = false;
                    }
                    if (hcl.length() != 7)
                    {
                        spdlog::info("invalid color length {}", hcl.length());
                        ok = false;
                    }

                    for (auto c : hcl.substr(1))
                    {
                        if (
                            ((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')))
                            ;
                        else
                        {
                            spdlog::info("invalid color character '{:c}'", c);
                            ok = false;
                        }
                    }
                }
                else if (words[0] == "ecl") // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth
                {
                    auto ecl = words[1];

                    if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" && ecl != "hzl" && ecl != "oth")
                    {
                        spdlog::info("invalid eye color: {}", ecl);
                        ok = false;
                    }
                }
                else if (words[0] == "pid") // pid (Passport ID) - a nine-digit number, including leading zeroes
                {
                    auto pid = words[1];
                    if (pid.length() != 9)
                    {
                        spdlog::info("invalid pid length {}", pid.length());
                        ok = false;
                    }
                    for (auto c : pid)
                    {
                        if ((c < '0') || (c > '9'))
                        {
                            spdlog::info("invalid pid character '{:c}'", c);
                            ok = false;
                        }
                    }
                }
            }
            if (ok)
            {
                size_t bit = required_fields[words[0]];
                rval |= (1 << bit);
                spdlog::debug("    bit {}", bit);
            }
        }
    }

    return rval;
}

template <typename OutputIterator>
OutputIterator parse_input(std::vector<std::string> const &raw_data, OutputIterator out, bool strict = false)
{
    field_t f = 0;

    for (auto d : raw_data)
    {
        if (d == "")
        {
            spdlog::debug("new field");
            spdlog::info("passport contains fields {:#02x}", f);
            *out++ = f;
            f = 0;
        }
        else
        {
            f |= get_fields(d, strict);
        }
    }

    return out;
}

void part(std::vector<field_t> const &passports)
{
    spdlog::info("Part 1");

    int count = 0;

    for (auto p : passports)
    {
        if (p == 0x7f)
        {
            count++;
        }
    }

    fmt::print("{} valid passports\n", count);
}

int main(int argc, char *argv[])
{
    absl::SetProgramUsageMessage(
        "Advent of Code - day 4");
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

    std::vector<field_t> passports;
    parse_input(input_strings, std::back_inserter(passports));

    std::vector<field_t> strict_passports;
    parse_input(input_strings, std::back_inserter(strict_passports), true);

    // fmt::print("parsed passports:\n");
    // for (auto i : passports)
    // {
    //     fmt::print("    {:#02x}\n", i);
    // }

    spdlog::info("Part 1");
    part(passports);

    spdlog::info("Part 2");
    part(strict_passports);

    return 0;
}