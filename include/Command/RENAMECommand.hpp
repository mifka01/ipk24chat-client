/**
 * @file include/Command/RENAMECommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"

namespace Command {

class RENAMECommand : public Command {
  /**
   * @class RENAMECommand
   * @brief Represents the RENAME command.
   *
   * The RENAME command is used to rename a channel on the chat server.
   */
 public:
  RENAMECommand();

  /**
   * @brief Executes the RENAME command.
   * @param protocol The protocol to use for communication.
   * @param message The message to execute.
   * @param client The client to execute the command for.
   */
  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Client& client) override;
};

}  // namespace Command
