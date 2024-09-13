#include "Client/State/AuthState.hpp"
#include "Client/State/OpenState.hpp"
#include "Command/AuthCommand.hpp"
#include "Command/JoinCommand.hpp"
#include "Command/RenameCommand.hpp"
#include <iostream>

void AuthState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }

  if (AuthCommand::match(message)) {
    AuthCommand command(client, message);
    command.execute();
  }

  if (JoinCommand::match(message) || RenameCommand::match(message)) {
    client.error("You are not authenticated");
    return;
  }

  client.error("Invalid command");
}

void AuthState::handleResponse() {
  std::unique_ptr<Message> response = client.receive();
  if (response == nullptr) {
    return;
  }

  handleMessage(*response);
}

void AuthState::handleReplyMessage(const ReplyMessage &message) {
  std::cerr << message.toString() << std::endl;

  if (!message.success) {
    client.setDisplayName("");
    return;
  }
  client.changeState(std::make_unique<OpenState>(client));
}
