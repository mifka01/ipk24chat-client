/**
 * @file src/Command/AUTHCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>

#include "Client/Client.hpp"
#include "Command/AUTHCommand.hpp"
#include "utils.hpp"

namespace Command {

AUTHCommand::AUTHCommand()
    : Command("auth",
              "/",
              {
                  Parameter("Username", "[a-zA-Z0-9\\-]", 20),
                  Parameter("Secret", "[a-zA-Z0-9\\-]", 128),
                  Parameter("DisplayName", "[\\x21-\\x7E]", 20),
              }) {}

void AUTHCommand::execute(std::shared_ptr<Protocol::Protocol> protocol,
                          const std::string& message,
                          Client::Client& client) {
  if (client.state == Client::State::OPEN) {
    std::cerr << "ERR: already authenticated\n";
    return;
  }
  std::vector<std::string> tokens = totokens(message);
  client.displayName = tokens[3];
  client.protocol->setNextState(Client::State::AUTH);
  tokens.erase(tokens.begin());

  protocol->send(protocol->toMessage(Message::Type::AUTH, tokens));
}

}  // namespace Command
