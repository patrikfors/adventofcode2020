#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

namespace
{
    int read_input(std::istream &in, std::vector<std::string> &output)
    {
        bool original_sync_state = std::ios_base::sync_with_stdio(false);

        std::string line;
        uint32_t lines_read = 0;
        while (std::getline(in, line))
        {
            output.emplace_back(line);
            lines_read++;
        }

        spdlog::info("Read {} lines.\n", lines_read);

        std::ios_base::sync_with_stdio(original_sync_state);
        return 0;
    }
} // namespace

namespace input
{
    int get_stdin_input(std::vector<std::string> &output)
    {
        return read_input(std::cin, output);
    }
    int get_file_input(std::string const &path, std::vector<std::string> &output)
    {
        std::ifstream file(path, std::ifstream::in);
        return read_input(file, output);
    }
} // namespace input

//   std::vector<std::string> args(argv, argv + argc);
//   std::vector<std::string> input;
//   get_input(args, input)