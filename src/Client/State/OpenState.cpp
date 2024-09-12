#include "Client/State/OpenState.hpp"
#include <iostream>

void OpenState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }
}

void OpenState::handleReplyMessage(const ReplyMessage &message) {
  if (message.success) {
    client.changeState(std::make_unique<OpenState>(client));
  }
}

void OpenState::handleResponse() {
  std::unique_ptr<Message> response = client.receive();
}
