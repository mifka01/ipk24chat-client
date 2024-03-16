#pragma once

#include <string>
#include <vector>
#include "Argument.hpp"
#include "Validator.hpp"

namespace ArgumentParser {
class Parser {
 public:
  void addArgument(const std::string& name,
                   const std::string& shortcut,
                   const Type type,
                   const std::string& help = "",
                   const std::string& defaultValue = "",
                   const int nargs = 1,
                   bool required = false);

  void addArgument(const std::string& name,
                   const Type type,
                   const std::string& help = "",
                   const int nargs = 1);

  std::unordered_map<std::string, std::string> parse(int argc, char* argv[]);

 private:
  Validator validator;
  std::vector<Argument> arguments;
};
}  // namespace ArgumentParser