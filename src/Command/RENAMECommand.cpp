#include "Command/RENAMECommand.hpp"
#include "utils.hpp"

namespace Command {

RENAMECommand::RENAMECommand()
    : Command("rename",
              "/",
              {
                  Parameter("DisplayName", "[\\x21-\\x7E]", 20),
              }) {}

void RENAMECommand::execute(__attribute__((unused))
                            Protocol::Protocol& protocol,
                            const std::string& message,
                            Client::Session& session) {
  std::vector<std::string> tokens = totokens(message);
  session.displayName = tokens[1];
}

}  // namespace Command
