#include "Client/State/OpenState.hpp"
#include "Client/State/EndState.hpp"
#include "Command/AuthCommand.hpp"
#include "Command/JoinCommand.hpp"
#include "Command/RenameCommand.hpp"
#include "Message/JoinMessage.hpp"
#include <iostream>

void OpenState::handleInput() {
  std::string message;
  std::getline(std::cin, message);

  if (message.empty()) {
    return;
  }

  if (AuthCommand::match(message)) {
    client.error("You are already authenticated");
    return;
  }

  if (JoinCommand::match(message)) {
    JoinCommand command(client, message);
    command.execute();
    return;
  }

  if (RenameCommand::match(message)) {
    RenameCommand command(client, message);
    command.execute();
    return;
  }

  client.send(MsgMessage(client.getDisplayName(), message));
}

void OpenState::handleResponse() {
  std::unique_ptr<Message> response = client.receive();

  if (response == nullptr) {
    return;
  }

  handleMessage(*response);
}

void OpenState::handleSigInt() {
  client.send(ByeMessage());
  client.changeState(std::make_unique<EndState>(client));
}

void OpenState::handleReplyMessage(const ReplyMessage &message) {
  std::cerr << message.toString() << std::endl;

  // There is only reply to JoinMessage that can be received in OpenState
  JoinMessage *joinMessage =
      dynamic_cast<JoinMessage *>(client.waitingForReply.get());

  if (joinMessage->id == message.refId || !client.protocol.needConfirmation()) {
    if (message.success) {
      client.setChannelId(joinMessage->channelId);
    }
    client.waitingForReply.reset();
  }
}
