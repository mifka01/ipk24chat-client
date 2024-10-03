#include "Client/State/ConfirmState.hpp"
#include <iostream>

void ConfirmState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }
}

void ConfirmState::handleResponse() {
  std::unique_ptr<Message> response = client.receive();

  if (response == nullptr) {
    return;
  }

  handleMessage(*response);
}
