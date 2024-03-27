#include "Command/AUTHCommand.hpp"
#include "Command/Command.hpp"
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

std::string AUTHCommand::generateMessage(Protocol::Type protocol,
                                         std::string message) {
  std::vector<std::string> tokens = totokens(message);

  if (tokens.size() != 4) {
    throw std::runtime_error("Invalid number of parameters");
  }

  switch (protocol) {
    case Protocol::Type::TCP:
      return "AUTH " + tokens[1] + " AS " + tokens[3] + " USING " + tokens[2] +
             "\r\n";
      break;
    case Protocol::Type::UDP:
      return "auth";
      break;
    default:
      throw std::runtime_error("Invalid protocol");
  }
}

}  // namespace Command
