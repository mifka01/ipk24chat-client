#include "Command/RENAMECommand.hpp"
#include "Client/Client.hpp"
#include "utils.hpp"

namespace Command {

RENAMECommand::RENAMECommand()
    : Command("rename",
              "/",
              {
                  Parameter("DisplayName", "[\\x21-\\x7E]", 20),
              }) {}

void RENAMECommand::execute(__attribute__((unused))
                            std::shared_ptr<Protocol::Protocol> protocol,
                            const std::string& message,
                            Client::Client& client) {
  std::vector<std::string> tokens = totokens(message);
  client.displayName = tokens[1];
}

}  // namespace Command
