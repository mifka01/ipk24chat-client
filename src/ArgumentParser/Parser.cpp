#include "ArgumentParser/Parser.hpp"
#include <iostream>
#include <string>

namespace ArgumentParser {

void Parser::parse(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    std::cout << arg << std::endl;
  }
}

void Parser::addArgument(const std::string& name,
                         const Type type,
                         const std::string& shortcut,
                         const std::string& help,
                         const std::string& defaultValue,
                         const int nargs,
                         bool required) {
  arguments.push_back(
      Argument(name, shortcut, type, help, defaultValue, nargs, required));
}

void Parser::addArgument(const std::string& name,
                         const Type type,
                         const std::string& help,
                         const int nargs) {
  arguments.push_back(Argument(name, type, help, nargs));
}
}  // namespace ArgumentParser
