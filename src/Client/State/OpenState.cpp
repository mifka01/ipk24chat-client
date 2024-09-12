#include "Client/State/OpenState.hpp"
#include <iostream>

void OpenState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }
}

void OpenState::handleResponse() {
  std::unique_ptr<Message> response = client.receive();

  if (response == nullptr) {
    return;
  }

  auto converter = messageConverters.find(response->type);
  if (converter == messageConverters.end()) {
    return;
  }
  converter->second(*response);
}
