#pragma once

#include <string>
#include <vector>

namespace input
{
    int get_file_input(std::string const &path, std::vector<std::string> &output);
    int get_stdin_input(std::vector<std::string> &output);
    int group_by_newline(std::vector<std::string> const &strings, std::vector<std::vector<std::string>> &string_groups);
} // namespace input