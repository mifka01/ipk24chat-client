/**
 * @file src/Command/RenameCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/RenameCommand.hpp"

const std::regex RenameCommand::PATTERN("^" + std::string(WHITESPACE_REGEX) +
                                            PREFIX + COMMAND_NAME +
                                            SPACE_REGEX + DISPLAY_NAME_REGEX +
                                            WHITESPACE_REGEX + "$",
                                        std::regex::icase);

bool RenameCommand::match(const std::string &message) {
  return std::regex_match(message, PATTERN);
}

RenameCommand::Parameters RenameCommand::parse(const std::string &message) {
  std::smatch match;
  if (!std::regex_match(message, match, PATTERN)) {
    throw std::invalid_argument("Invalid message format");
  }

  return Parameters{match[1]};
}

void RenameCommand::execute() const { client.setDisplayName(getDisplayName()); }
