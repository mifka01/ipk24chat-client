/**
 * @file src/Command/AuthCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/AuthCommand.hpp"
#include "Client/State/AuthState.hpp"
#include "Message/AuthMessage.hpp"

const std::regex
    AuthCommand::PATTERN("^" + std::string(WHITESPACE_REGEX) + PREFIX +
                             COMMAND_NAME + SPACE_REGEX + USERNAME_REGEX +
                             SPACE_REGEX + SECRET_REGEX + SPACE_REGEX +
                             DISPLAY_NAME_REGEX + WHITESPACE_REGEX + "$",
                         std::regex::icase);

bool AuthCommand::match(const std::string &message) {
  return std::regex_match(message, PATTERN);
}

Parameters AuthCommand::parse(const std::string &message) {
  std::smatch match;
  if (!std::regex_match(message, match, PATTERN)) {
    throw std::invalid_argument("Invalid message format");
  }

  return Parameters{match[1], match[2], match[3]};
}

void AuthCommand::execute() const {
  client.send(AuthMessage(getUsername(), getDisplayName(), getSecret()));
  client.setDisplayName(getDisplayName());
  client.changeState(std::make_unique<AuthState>(client));
}
