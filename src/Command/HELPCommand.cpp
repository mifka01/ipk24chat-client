#include "Command/HELPCommand.hpp"
#include <iostream>
#include <string>

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
