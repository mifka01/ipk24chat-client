/**
 * @file src/Command/Command.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/Command.hpp"

namespace Command {

Command::Command(const std::string& name,
                 const std::string& prefix,
                 const std::vector<Parameter>& parameters)
    : name(name), prefix(prefix), parameters(parameters) {
  generateRegex();
}

void Command::generateRegex() {
  std::regex name_regex(COMMAND_NAME_REGEX);

  if (!std::regex_match(name, name_regex)) {
    throw std::runtime_error("Invalid command name");
  }

  std::string pattern = "^\\" + prefix + name;

  for (const Parameter& parameter : parameters) {
    pattern += " " + parameter.getPattern();
  }
  pattern += WHITESPACE_REGEX + "$";

  try {
    regex = std::regex(pattern);
  } catch (std::regex_error& e) {
    throw std::runtime_error("Failed to build regex: " + std::string(e.what()));
  }
}

bool Command::match(const std::string& message) const {
  return std::regex_match(message, regex);
}

const std::string& Command::getPrefix() const {
  return prefix;
}

}  // namespace Command
