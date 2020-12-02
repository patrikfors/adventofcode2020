#include <iostream>
#include <string>
#include <vector>

#include "input.h"

int main(int argc, char *argv[])
{
   std::vector<std::string> args(argv, argv + argc);
   std::vector<std::string> input;
   input::get_input(args, input);

   for(auto x : input) {
       std::cout << x << std::endl;
   }

   return 0;
}