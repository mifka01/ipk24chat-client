/**
 * @file include/Command/CommandRegistry.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <map>

#include "Command.hpp"

namespace Command {

class CommandRegistry {
  /**
   * @class CommandRegistry
   * @brief Represents a registry of commands.
   *
   * The CommandRegistry class provides functionality for storing and retrieving
   * commands by name.
   */
 public:
  std::map<std::string, std::unique_ptr<Command>> commands;
  std::vector<std::string> prefixes;

  /**
   * @brief Adds a command to the registry.
   * @param name The name of the command.
   * @param command The command to add.
   */
  void add(const std::string& name, std::unique_ptr<Command> command);

  /**
   * @brief Retrieves a command from the registry.
   * @param name The name of the command.
   * @return The command with the specified name.
   */
  Command* getCommand(const std::string& name);
};

}  // namespace Command
