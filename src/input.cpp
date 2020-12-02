#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int read_input(std::istream &in, std::vector<std::string> output)
{
    std::string line;
    uint32_t lines_read = 0;
    while (std::getline(in, line))
    {
        output.emplace_back(line);
        lines_read++;
    }

    //   if (FLAGS_v) {
    //     fmt::print("Read {} lines.\n", lines_read);
    //   }

    return 0;
}

int get_input(std::vector<std::string> args, std::vector<std::string> output)
{
    bool original_sync_state = std::ios_base::sync_with_stdio(false);

    if (args.size() > 0)
    {
        std::ifstream file(args[1], std::ifstream::in);
        read_input(file, output);
    }
    else
    {
        read_input(std::cin, output);
    }

    std::ios_base::sync_with_stdio(original_sync_state);
    return 0;
}

//   std::vector<std::string> args(argv, argv + argc);
//   std::vector<std::string> input;
//   get_input(args, input)