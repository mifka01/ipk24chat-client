#include "Client/State/StartState.hpp"
#include "Command/AuthCommand.hpp"
#include "Message/AuthMessage.hpp"
#include <iostream>

void StartState::processInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }

  if (AuthCommand::match(message)) {
    AuthCommand command(client, message);
    command.execute();
  }
}
