/**
 * @file src/Command/HELPCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>
#include <string>

#include "Command/HELPCommand.hpp"

namespace Command {

HELPCommand::HELPCommand() : Command("help", "/", {}) {}

void HELPCommand::execute(__attribute__((unused))
                          std::shared_ptr<Protocol::Protocol> protocol,
                          __attribute__((unused)) const std::string& message,
                          __attribute__((unused)) Client::Client& client) {
  std::cout << "Commands:" << std::endl;
  std::cout << " /auth {Username} {Secret} {DisplayName}" << std::endl;
  std::cout << " /join {ChannelID}" << std::endl;
  std::cout << " /rename {DisplayName}" << std::endl;
  std::cout << " /help" << std::endl;
  // exit
}

}  // namespace Command
