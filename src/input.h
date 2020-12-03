#pragma once

#include <string>
#include <vector>

namespace input {
int get_file_input(std::string const& path, std::vector<std::string>& output);
int get_stdin_input(std::vector<std::string>& output);
}