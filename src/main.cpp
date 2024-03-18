/**
 * @file src/main.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>
#include "arguments.hpp"

int main(int argc, char* argv[]) {
  try {
    std::unordered_map<std::string, std::string> args =
        parse_arguments(argc, argv);
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
