/**
 * @file include/Command/AUTHCommand.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Command/Command.hpp"

namespace Command {

class AUTHCommand : public Command {
  /**
   * @class AUTHCommand
   * @brief Represents the AUTH command.
   *
   * The AUTH command is used to authenticate a client with the chat server.
   */

 public:
  AUTHCommand();

  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Client& client) override;
};

}  // namespace Command
