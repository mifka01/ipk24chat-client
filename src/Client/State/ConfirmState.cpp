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

void ConfirmState::onEnter() {
  int events = client.poller.poll(250);

  if (events < 0) {

    if (client.poller.hasEvent(1, POLLIN)) {
      handleResponse();
    }

    if (client.poller.hasEvent(0, POLLIN)) {
      handleInput();
    }
  }
}
