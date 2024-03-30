#include "Command/AUTHCommand.hpp"
#include <iostream>
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

void AUTHCommand::execute(Protocol::Protocol& protocol,
                          const std::string& message,
                          Client::Session& session) {
  if (session.state == Client::State::OPEN) {
    std::cerr << "ERR: already authenticated\n";
    return;
  }
  std::vector<std::string> tokens = totokens(message);
  session.displayName = tokens[3];
  session.state = Client::State::AUTH;
  tokens.erase(tokens.begin());

  protocol.send(session.socket,
                protocol.toMessage(Message::Type::AUTH, tokens, session));
}

}  // namespace Command
