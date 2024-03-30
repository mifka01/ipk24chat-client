#include "Command/JOINCommand.hpp"
#include <iostream>
#include "utils.hpp"

namespace Command {

JOINCommand::JOINCommand()
    : Command("join",
              "/",
              {
                  Parameter("ChannelID", "[a-zA-Z0-9\\-]", 20),
              }) {}

void JOINCommand::execute(std::shared_ptr<Protocol::Protocol> protocol,
                          const std::string& message,
                          Client::Session& session) {
  if (session.state != Client::State::OPEN) {
    std::cerr << "ERR: trying to send a message in non-open state\n";
    return;
  }
  std::vector<std::string> tokens = totokens(message);
  tokens.erase(tokens.begin());
  protocol->send(session.socket,
                protocol->toMessage(Message::Type::JOIN, tokens));
}

}  // namespace Command
