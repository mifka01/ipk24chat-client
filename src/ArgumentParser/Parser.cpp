#include "ArgumentParser/Parser.hpp"
#include <string>
#include <unordered_map>

namespace ArgumentParser {

std::unordered_map<std::string, std::string> Parser::parse(int argc,
                                                           char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  std::unordered_map<std::string, std::string> parsedArgs;
  int positionalCount = 0;

  for (Argument arg : arguments) {
    if (arg.isPositional) {
      if (validator.validate(arg.getType(), args[positionalCount])) {
        parsedArgs[arg.getName()] = args[positionalCount];
      }
      positionalCount++;
    } else {
    }
  }

  return parsedArgs;
}

void Parser::addArgument(const std::string& name,
                         const std::string& shortcut,
                         const Type type,
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
