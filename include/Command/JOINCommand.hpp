/**
 * @file include/Command/JOINCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"

namespace Command {

class JOINCommand : public Command {
 public:
  /**
   * @class JOINCommand
   * @brief Represents the JOIN command.
   *
   * The JOIN command is used to join channel on the chat server.
   */
  JOINCommand();

  /**
   * @brief Executes the JOIN command.
   * @param protocol The protocol to use for communication.
   * @param message The message to execute.
   * @param client The client to execute the command for.
   */
  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Client& client) override;
};

}  // namespace Command
