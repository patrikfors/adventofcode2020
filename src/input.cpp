#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    int read_input(std::istream &in, std::vector<std::string> &output)
    {
        std::string line;
        uint32_t lines_read = 0;
        while (std::getline(in, line))
        {
            output.emplace_back(line);
            lines_read++;
        }

        std::cout << "read " << lines_read << " lines" << std::endl;
        //   if (FLAGS_v) {
        //     fmt::print("Read {} lines.\n", lines_read);
        //   }

        return 0;
    }
} // namespace

namespace input
{
    int get_input(std::vector<std::string> args, std::vector<std::string> &output)
    {
        bool original_sync_state = std::ios_base::sync_with_stdio(false);

        if (args.size() > 1)
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
} // namespace input

//   std::vector<std::string> args(argv, argv + argc);
//   std::vector<std::string> input;
//   get_input(args, input)