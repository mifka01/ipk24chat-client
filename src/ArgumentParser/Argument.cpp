#include "ArgumentParser/Argument.hpp"

namespace ArgumentParser {

Argument::Argument(const std::string& name,
                   const Type type,
                   const std::string& help,
                   const std::vector<std::string>& choices,
                   const int nargs)
    : name(name),
      type(type),
      help(help),
      choices(choices),
      nargs(nargs),
      isRequired(true),
      isPositional(true) {
  if (choices.size() > 0) {
    for (std::string s : choices) {
      transform(s.begin(), s.end(), s.begin(), ::toupper);
    }
  }
  if (name.empty()) {
    throw std::invalid_argument("Name cannot be empty");
  }
  if (nargs != 1) {
    throw std::invalid_argument("Positional arguments cannot have nargs != 1");
  }
}

Argument::Argument(const std::string& name,
                   const std::string& shortcut,
                   const Type type,
                   const std::string& help,
                   const std::string& defaultValue,
                   const std::vector<std::string>& choices,
                   const int nargs,
                   bool required)
    : name(name),
      shortcut(shortcut),
      type(type),
      help(help),
      defaultValue(defaultValue),
      choices(choices),
      nargs(nargs),
      isRequired(required),
      isPositional(false) {
  if (choices.size() > 0) {
    for (std::string s : choices) {
      transform(s.begin(), s.end(), s.begin(), ::toupper);
    }
  }
  if (name.empty()) {
    throw std::invalid_argument("Name cannot be empty");
  }

  if (name.size() < 2 || name.substr(0, 2) != "--") {
    throw std::invalid_argument("Option must start with '--'");
  }

  if (!shortcut.empty() && shortcut[0] != '-') {
    throw std::invalid_argument("Shortcut must start with a '-'");
  }
}

std::string Argument::getName() const {
  return name;
}
std::string Argument::getShortcut() const {
  return shortcut;
}
std::string Argument::getHelp() const {
  return help;
}
Type Argument::getType() const {
  return type;
}
int Argument::getNargs() const {
  return nargs;
}

std::vector<std::string> Argument::getChoices() const {
  return choices;
}

std::string Argument::getDefaultValue() const {
  return defaultValue;
}
}  // namespace ArgumentParser
