/**
 * @file include/Command/JoinCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"
#include <regex>

class JoinCommand : public Command {

  struct Parameters {
    const std::string channelId;
  };

private:
  Parameters parameters;
  static constexpr const char *COMMAND_NAME = "join";

  static constexpr const char *CHANNEL_ID = "([a-zA-Z0-9\\-]{1,20})";

  static const std::regex PATTERN;

  /**
   * @class JoinCommand
   * @brief Represents the Join command.
   *
   * The Join command is used to join a channel.
   */
public:
  JoinCommand(Client &client, const std::string &message)
      : Command(client, COMMAND_NAME), parameters(parse(message)) {}

  JoinCommand(Client &client, const Parameters &parameters)
      : Command(client, COMMAND_NAME), parameters(parameters) {}

  static bool match(const std::string &message);
  static Parameters parse(const std::string &message);

  const std::string &getChannelId() const { return parameters.channelId; }

  void execute() const override;
};
