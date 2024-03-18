#pragma once

#include <string>
#include <vector>
#include "Argument.hpp"
#include "Validator.hpp"

namespace ArgumentParser {
class Parser {
  Validator validator;
  std::vector<Argument> positional;
  std::vector<Argument> options;
  std::vector<Argument> flags;

  std::vector<std::string>::const_iterator findArg(
      const std::vector<std::string>& args,
      const std::string& name,
      const std::string& shortcut);

  void parsePositional(
      const std::vector<std::string>& args,
      std::unordered_map<std::string, std::string>& parsedArgs);

  void parseOptions(const std::vector<std::string>& args,
                    std::unordered_map<std::string, std::string>& parsedArgs);

  void parseFlags(const std::vector<std::string>& args,
                  std::unordered_map<std::string, std::string>& parsedArgs);

 public:
  // FLAG
  void addArgument(const std::string& name,
                   const std::string& shortcut,
                   const std::string& help = "",
                   bool required = false);

  // POSITIONAL
  void addArgument(const std::string& name,
                   const Type type,
                   const std::string& help = "",
                   const int nargs = 1);

  void addArgument(const std::string& name,
                   const Type type,
                   const std::string& help = "",
                   const std::vector<std::string>& choices = {},
                   const int nargs = 1);

  // OPTION
  void addArgument(const std::string name,
                   const std::string shortcut,
                   const Type type,
                   const std::string help = "",
                   bool required = false,
                   const std::string& defaultValue = "",
                   const std::vector<std::string> choices = {},
                   const int nargs = 1);

  std::unordered_map<std::string, std::string> parse(int argc, char* argv[]);
};
}  // namespace ArgumentParser
