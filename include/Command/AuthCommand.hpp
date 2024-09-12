/**
 * @file include/Command/AuthCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"
#include <regex>

class AuthCommand : public Command {

  struct Parameters {
    const std::string username;
    const std::string secret;
    const std::string displayName;
  };

private:
  Parameters parameters;

  static constexpr const char *COMMAND_NAME = "auth";

  static constexpr const char *USERNAME_REGEX = "([a-zA-Z0-9\\-]{1,20})";
  static constexpr const char *SECRET_REGEX = "([a-zA-Z0-9\\-]{1,128})";
  static constexpr const char *DISPLAY_NAME_REGEX = "([\\x21-\\x7E]{1,20})";

  static const std::regex PATTERN;

  /**
   * @class AuthCommand
   * @brief Represents the Auth command.
   *
   * The Auth command is used to authenticate a client with the chat server.
   */
public:
  AuthCommand(Client &client, const std::string &username,
              const std::string &secret, const std::string &displayName)
      : Command(client, COMMAND_NAME),
        parameters{username, secret, displayName} {}

  AuthCommand(Client &client, const Parameters &parameters)
      : Command(client, COMMAND_NAME), parameters(parameters) {}

  AuthCommand(Client &client, const std::string &message)
      : Command(client, COMMAND_NAME), parameters(parse(message)) {}

  static bool match(const std::string &message);
  static Parameters parse(const std::string &message);

  const std::string &getUsername() const { return parameters.username; }
  const std::string &getSecret() const { return parameters.secret; }
  const std::string &getDisplayName() const { return parameters.displayName; }

  void execute() const override;
};
