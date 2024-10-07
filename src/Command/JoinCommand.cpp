/**
 * @file src/Command/JoinCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/JoinCommand.hpp"
#include "Message/JoinMessage.hpp"
#include <sstream>

const std::regex JoinCommand::PATTERN("^" + std::string(WHITESPACE_REGEX) +
                                          PREFIX + COMMAND_NAME + SPACE_REGEX +
                                          CHANNEL_ID + WHITESPACE_REGEX + "$",
                                      std::regex::icase);

bool JoinCommand::match(const std::string &message) {
  return std::regex_match(message, PATTERN);
}

JoinCommand::Parameters JoinCommand::parse(const std::string &message) {
  std::smatch match;
  if (!std::regex_match(message, match, PATTERN)) {
    throw std::invalid_argument("Invalid message format");
  }

  return Parameters{match[1]};
}

void JoinCommand::execute() const {
  if (client.getChannelId() == getChannelId()) {
    std::ostringstream oss;
    oss << "You are already in " << getChannelId() << " channel";
    client.error(oss.str());
    return;
  }

  client.send(
      std::make_unique<JoinMessage>(getChannelId(), client.getDisplayName()));
}
