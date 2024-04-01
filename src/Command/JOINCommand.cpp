/**
 * @file src/Command/JOINCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>
#include "utils.hpp"

#include "Client/Client.hpp"
#include "Command/JOINCommand.hpp"

namespace Command {

JOINCommand::JOINCommand()
    : Command("join",
              "/",
              {
                  Parameter("ChannelID", "[a-zA-Z0-9\\-]", 20),
              }) {}

void JOINCommand::execute(std::shared_ptr<Protocol::Protocol> protocol,
                          const std::string& message,
                          Client::Client& client) {
  if (client.state != Client::State::OPEN) {
    std::cerr << "ERR: trying to send a message in non-open state\n";
    return;
  }
  std::vector<std::string> tokens = totokens(message);
  tokens.erase(tokens.begin());
  protocol->send(protocol->toMessage(Message::Type::JOIN, tokens));
}

}  // namespace Command
