#include "Client/State/StartState.hpp"
#include "Client/State/AuthState.hpp"
#include "Command/AuthCommand.hpp"
#include "Message/AuthMessage.hpp"
#include <iostream>

void StartState::run() {
  while (true) {
    int events = client.poller.poll();
    if (events < 0) {
      throw std::runtime_error("Failed to poll");
    }

    if (client.poller.hasEvent(0, POLLIN)) {
      std::string message;
      std::getline(std::cin, message);

      if (message.empty()) {
        return;
      }
      if (AuthCommand::match(message)) {
        std::cout << "Auth command" << std::endl;
      }
    }
  }
}
