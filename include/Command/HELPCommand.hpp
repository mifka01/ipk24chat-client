/**
 * @file include/Command/HELPCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"

namespace Command {

class HELPCommand : public Command {
 public:
  /**
   * @class HELPCommand
   * @brief Represents the HELP command.
   *
   * The HELP command is used to display a list of available commands.
   */
  HELPCommand();

  /**
   * @brief Executes the HELP command.
   * @param protocol The protocol to use for communication.
   * @param message The message to execute.
   * @param client The client to execute the command for.
   */
  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Client& client) override;
};

}  // namespace Command
