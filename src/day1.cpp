#include <string>
#include <vector>

#include "input.h"

int main(int argc, char *argv[])
{
   std::vector<std::string> args(argv, argv + argc);
   std::vector<std::string> input;
   get_input(args, input);

   return 0;
}