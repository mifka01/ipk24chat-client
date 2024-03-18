#include "ArgumentParser/Parser.hpp"
#include <string>
#include <unordered_map>

namespace ArgumentParser {
std::unordered_map<std::string, std::string> Parser::parse(int argc,
                                                           char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  std::unordered_map<std::string, std::string> parsedArgs;

  parsePositional(args, parsedArgs);
  parseOptions(args, parsedArgs);
  parseFlags(args, parsedArgs);

  return parsedArgs;
}

std::vector<std::string>::const_iterator Parser::findArg(
    const std::vector<std::string>& args,
    const std::string& name,
    const std::string& shortcut) {
  std::vector<std::string>::const_iterator foundByName =
      std::find(args.begin(), args.end(), name);
  if (foundByName != args.end()) {
    return foundByName;
  }
  return std::find(args.begin(), args.end(), shortcut);
}

void Parser::parsePositional(
    const std::vector<std::string>& args,
    std::unordered_map<std::string, std::string>& parsedArgs) {
  for (size_t i = 0; i < positional.size(); ++i) {
    Argument& arg = positional[i];
    const std::string& argValue = args[i];

    if (validator.validateType(arg.getType(), argValue) &&
        validator.validateChoices(argValue, arg.getChoices())) {
      parsedArgs[arg.getName()] = argValue;
    } else {
      throw std::invalid_argument(
          "Invalid value: '" + argValue +
          "' for positional argument: " + arg.getName());
    }
  }
}

void Parser::parseOptions(
    const std::vector<std::string>& args,
    std::unordered_map<std::string, std::string>& parsedArgs) {
  for (Argument& arg : options) {
    auto it = findArg(args, arg.getName(), arg.getShortcut());

    // if the argument is not found
    if (it == args.end()) {
      if (arg.isRequired) {
        throw std::invalid_argument("Missing required option: " +
                                    arg.getName());
      } else if (!arg.getDefaultValue().empty()) {
        parsedArgs[arg.getName()] = arg.getDefaultValue();
      }
      continue;
    }

    auto nextArg = it + 1;
    if (nextArg != args.end() &&
        validator.validateType(arg.getType(), *nextArg) &&
        validator.validateChoices(*nextArg, arg.getChoices())) {
      parsedArgs[arg.getName()] = *nextArg;
    } else {
      throw std::invalid_argument("Invalid value: '" + *nextArg +
                                  "' for option: " + arg.getName());
    }
  }
}

void Parser::parseFlags(
    const std::vector<std::string>& args,
    std::unordered_map<std::string, std::string>& parsedArgs) {
  for (Argument& arg : flags) {
    auto it = findArg(args, arg.getName(), arg.getShortcut());
    if (it != args.end()) {
      parsedArgs[arg.getName()] = "true";
      continue;
    }
    if (arg.isRequired) {
      throw std::invalid_argument("Missing required flag: " + arg.getName());
    }
  }
}

// FLAG
void Parser::addArgument(const std::string& name,
                         const std::string& shortcut,
                         const std::string& help,
                         bool required) {
  flags.push_back(
      Argument(name, shortcut, Type::FLAG, help, "", {}, 0, required));
}

// POSITIONAL
void Parser::addArgument(const std::string& name,
                         const Type type,
                         const std::string& help,
                         const int nargs) {
  positional.push_back(Argument(name, type, help, {}, nargs));
}

void Parser::addArgument(const std::string& name,
                         const Type type,
                         const std::string& help,
                         const std::vector<std::string>& choices,
                         const int nargs) {
  positional.push_back(Argument(name, type, help, choices, nargs));
}

// OPTION
void Parser::addArgument(const std::string name,
                         const std::string shortcut,
                         const Type type,
                         const std::string help,
                         bool required,
                         const std::string& defaultValue,
                         const std::vector<std::string> choices,
                         const int nargs) {
  options.push_back(Argument(name, shortcut, type, help, defaultValue, choices,
                             nargs, required));
}

}  // namespace ArgumentParser
