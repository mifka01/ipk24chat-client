/**
 * @file include/Command/AuthCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"
#include <regex>

class AuthCommand : public Command {

private:
  const std::string username;
  const std::string secret;
  const std::string displayName;

  static constexpr const char *COMMAND_NAME = "auth";

  static constexpr const char *USERNAME_REGEX = "[a-zA-Z0-9\\-]{1,20}";
  static constexpr const char *SECRET_REGEX = "[a-zA-Z0-9\\-]{1,128}";
  static constexpr const char *DISPLAY_NAME_REGEX = "[\\x21-\\x7E]{1,20}";

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
      : Command(client, COMMAND_NAME), username(username), secret(secret),
        displayName(displayName) {}

  static bool match(const std::string &message) {
    return std::regex_match(message, PATTERN);
  }

  void execute() const override;
};
