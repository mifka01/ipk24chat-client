#include <iostream>
#include "arguments.hpp"

int main(int argc, char* argv[]) {
  std::unordered_map<std::string, std::string> args =
      parse_arguments(argc, argv);

  for (auto& arg : args) {
    std::cout << arg.first << " " << arg.second << std::endl;
  }
  return 0;
}
