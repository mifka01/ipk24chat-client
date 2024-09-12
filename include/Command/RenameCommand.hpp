/**
 * @file include/Command/RenameCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"
#include <regex>

class RenameCommand : public Command {
  struct Parameters {
    const std::string displayName;
  };

private:
  Parameters parameters;

  static constexpr const char *COMMAND_NAME = "rename";

  static constexpr const char *DISPLAY_NAME_REGEX = "([\\x21-\\x7E]{1,20})";

  static const std::regex PATTERN;

  /**
   * @class RenameCommand
   * @brief Represents the Rename command.
   *
   * The Rename command is used to change client's display name.
   */
public:
  RenameCommand(Client &client, const std::string &displayName)
      : Command(client, COMMAND_NAME), parameters{displayName} {}

  RenameCommand(Client &client, const Parameters &parameters)
      : Command(client, COMMAND_NAME), parameters(parameters) {}

  static bool match(const std::string &message);
  static Parameters parse(const std::string &message);

  const std::string &getDisplayName() const { return parameters.displayName; }

  void execute() const override;
};
