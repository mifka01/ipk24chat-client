#include "Client/State/State.hpp"
#include "Client/State/EndState.hpp"
#include <iostream>

void State::handleReplyMessage(const ReplyMessage &message) { (void)message; }

void State::handleErrMessage(const ErrMessage &message) {
  std::cerr << message.toString() << std::endl;
  client.send(ByeMessage());
  client.changeState(std::make_unique<EndState>(client));
}

void State::handleMsgMessage(const MsgMessage &message) {
  std::cout << message.toString() << std::endl;
}

void State::handleByeMessage(const ByeMessage &message) {
  (void)message;
  client.changeState(std::make_unique<EndState>(client));
}
