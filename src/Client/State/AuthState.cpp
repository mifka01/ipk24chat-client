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
    return;
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

  if (!client.protocol.needConfirmation() ||
      client.waitingForReply->id == message.refId) {
    if (message.success) {
      client.changeState(std::make_unique<OpenState>(client));
    } else {
      client.setDisplayName("");
    }
    client.waitingForReply.reset();
  }
}

void AuthState::handleConfirmMessage(const ConfirmMessage &message) {
  if (!client.protocol.needConfirmation()) {
    return;
  }

  if (client.waitingForConfirm->id != message.refId) {
    return;
  }

  if (client.waitingForConfirm->type == MessageType::AUTH ||
      client.waitingForConfirm->type == MessageType::JOIN) {
    client.waitingForReply = std::move(client.waitingForConfirm);
  }

  client.waitingForConfirm.reset();
}
