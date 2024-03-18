#include "ArgumentParser/Parser.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

namespace ArgumentParser {
Parser::Parser(std::string programName) : programName(programName) {
  flags.push_back(Argument("--help", "-h", Type::HELP,
                           "Prints program help output and exits", "", {}, 0,
                           false));
}
std::unordered_map<std::string, std::string> Parser::parse(int argc,
                                                           char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  std::unordered_map<std::string, std::string> parsedArgs;

  parseFlags(args, parsedArgs);
  parsePositional(args, parsedArgs);
  parseOptions(args, parsedArgs);

  return parsedArgs;
}

std::vector<std::string>::const_iterator Parser::findArg(
    const std::vector<std::string>& args,
    const std::string& name,
    const std::string& shortcut) {
  const std::vector<std::string>::const_iterator foundByName =
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

    if (validator.validate(arg, argValue)) {
      parsedArgs[arg.getName()] = argValue;
    } else {
      printUsage();
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
        printUsage();
        throw std::invalid_argument("Missing required option: " +
                                    arg.getName());
      } else if (!arg.getDefaultValue().empty()) {
        if (!validator.validateType(arg.getType(), arg.getDefaultValue())) {
          throw std::invalid_argument("Invalid default value: '" +
                                      arg.getDefaultValue() +
                                      "' for option: " + arg.getName());
        }
        parsedArgs[arg.getName()] = arg.getDefaultValue();
      }
      continue;
    }

    auto nextArg = it + 1;
    if (nextArg != args.end() && validator.validate(arg, *nextArg)) {
      parsedArgs[arg.getName()] = *nextArg;
    } else {
      printUsage();
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
    if (it != args.end() && arg.getType() == Type::HELP) {
      printHelp();
      exit(0);
    }
    if (it != args.end()) {
      parsedArgs[arg.getName()] = "true";
      continue;
    }
    if (arg.isRequired) {
      printUsage();
      throw std::invalid_argument("Missing required flag: " + arg.getName());
    }
  }
}

// FLAG
void Parser::addArgument(const std::string& name,
                         const std::string& shortcut,
                         const std::string& help,
                         const bool& required) {
  flags.push_back(
      Argument(name, shortcut, Type::FLAG, help, "", {}, 0, required));
}

// POSITIONAL
void Parser::addArgument(const std::string& name,
                         const Type& type,
                         const std::string& help,
                         const int& nargs) {
  positional.push_back(Argument(name, type, help, {}, nargs));
}

void Parser::addArgument(const std::string& name,
                         const Type& type,
                         const std::string& help,
                         const std::vector<std::string>& choices,
                         const int& nargs) {
  validateChoices(type, choices);
  positional.push_back(Argument(name, type, help, choices, nargs));
}

// OPTION
void Parser::addArgument(const std::string& name,
                         const std::string& shortcut,
                         const Type& type,
                         const std::string& help,
                         const bool& required,
                         const std::string& defaultValue,
                         const std::vector<std::string>& choices,
                         const int& nargs) {
  validateChoices(type, choices);
  options.push_back(Argument(name, shortcut, type, help, defaultValue, choices,
                             nargs, required));
}

void Parser::validateChoices(const Type& type,
                             const std::vector<std::string>& choices) {
  for (const std::string& s : choices) {
    if (!validator.validateType(type, s)) {
      throw std::invalid_argument("Invalid type of choice: " + s);
    }
  }
}

void Parser::printUsage() {
  std::cout << "usage: " << programName << " ";

  for (Argument& arg : positional) {
    std::cout << arg.getName() << " " << toString(arg.getType()) << " ";
  }

  for (Argument& arg : options) {
    if (arg.isRequired) {
      std::cout << arg.getShortcut() << " " << toString(arg.getType()) << " ";
    } else {
      std::cout << "[" << arg.getShortcut() << " " << toString(arg.getType())
                << "] ";
    }
  }

  for (Argument& arg : flags) {
    if (arg.isRequired) {
      std::cout << arg.getShortcut() << " ";
    } else {
      std::cout << "[" << arg.getShortcut() << "] ";
    }
  }
  std::cout << std::endl;
}
void Parser::printHelp() {
  printUsage();
  std::cout << std::endl;

  const int fieldWidth = 40;

  if (positional.size() > 0) {
    std::cout << "positional:" << std::endl;
    for (Argument& arg : positional) {
      std::string val = toString(arg.getType());

      if (arg.getChoices().size() > 0) {
        val += " (";
        for (size_t i = 0; i < arg.getChoices().size(); ++i) {
          val += arg.getChoices()[i];
          if (i != arg.getChoices().size() - 1) {
            val += ", ";
          }
        }
      }
      std::cout << "  " << std::left << std::setw(fieldWidth)
                << (arg.getName() + " " + val) << " " << std::left
                << std::setw(10) << arg.getHelp() << std::endl;
    }
  }

  std::cout << std::endl;

  if (flags.size() > 0) {
    std::cout << "flags:" << std::endl;
    for (Argument& arg : flags) {
      std::cout << "  " << std::left << std::setw(fieldWidth)
                << (arg.getShortcut() + ", " + arg.getName()) << " "
                << std::left << std::setw(10) << arg.getHelp() << std::endl;
    }
  }

  std::cout << std::endl;

  if (options.size() > 0) {
    std::cout << "options:" << std::endl;
    for (Argument& arg : options) {
      std::string val = toString(arg.getType());

      if (arg.getDefaultValue() != "") {
        val += " (default: " + arg.getDefaultValue() + ")";
      }
      if (arg.getChoices().size() > 0) {
        val += " (";
        for (size_t i = 0; i < arg.getChoices().size(); ++i) {
          val += arg.getChoices()[i];
          if (i != arg.getChoices().size() - 1) {
            val += ", ";
          }
        }
        val += ")";
      }
      std::cout << "  " << std::left << std::setw(fieldWidth)
                << (arg.getShortcut() + ", " + arg.getName() + " " + val) << " "
                << std::left << std::setw(15) << arg.getHelp() << std::endl;
    }
  }
}
}  // namespace ArgumentParser
