#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "input.h"

using int_t = uint32_t;

int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv + argc);
    std::vector<std::string> input_strings;
    input::get_input(args, input_strings);

    std::vector<int_t> input;

    std::transform(input_strings.begin(), input_strings.end(), std::back_inserter(input),
                   [](std::string s) -> int_t { 
                       return std::stol(s); });

    std::unordered_set<int_t> data(std::begin(input), std::end(input));

    for (auto d : data)
    {
        if (data.count(2020-d)) {
            std::cout << "Found matching set: " << d << ", " << (2020-d) << std::endl;
            std::cout << "Product is: " << d*(2020-d) << std::endl;
        }
        
    }

    return 0;
}