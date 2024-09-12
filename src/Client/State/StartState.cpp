#include "Client/State/StartState.hpp"
#include "Command/AuthCommand.hpp"
#include "Command/JoinCommand.hpp"
#include "Command/RenameCommand.hpp"
#include <iostream>

void StartState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }

  if (AuthCommand::match(message)) {
    AuthCommand command(client, message);
    command.execute();
    return;
  }

  if (JoinCommand::match(message) || RenameCommand::match(message)) {
    client.error("You are not authenticated");
    return;
  }

  client.error("Invalid command");
}
