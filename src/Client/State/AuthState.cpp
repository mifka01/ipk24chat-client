#include "Client/State/AuthState.hpp"
#include "Client/State/EndState.hpp"
#include "Client/State/OpenState.hpp"
#include "Command/AuthCommand.hpp"
#include "Message/ByeMessage.hpp"
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
}

void AuthState::handleReplyMessage(const ReplyMessage &message) {
  std::cerr << message.toString() << std::endl;

  if (!message.success) {
    client.setDisplayName("");
    return;
  }
  client.changeState(std::make_unique<OpenState>(client));
}

void AuthState::handleErrMessage(const ErrMessage &message) {
  std::cerr << message.toString() << std::endl;
  client.send(ByeMessage());
  client.changeState(std::make_unique<EndState>(client));
}

void AuthState::handleResponse() {
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
