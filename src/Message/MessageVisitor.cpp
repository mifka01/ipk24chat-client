/**
 * @file src/Message/MessageVisitor.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>

#include "Client/Client.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MessageVisitor.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"

namespace Message {

void MessageVisitor::visit(ErrMessage& err) {
  std::cerr << "ERR FROM " << err.displayName << ": " << err.content << "\n";
  client.state = Client::State::END;
}

void MessageVisitor::visit(ReplyMessage& reply) {
  if (reply.success) {
    std::cerr << "Success: " << reply.content << "\n";
    if (client.state == Client::State::AUTH)
      client.state = Client::State::OPEN;
  } else {
    if (client.state == Client::State::AUTH)
      client.state = Client::State::START;
    std::cerr << "Failure: " << reply.content << "\n";
  }
}

void MessageVisitor::visit(MsgMessage& msg) {
  std::cout << msg.displayName << ": " << msg.content << "\n";
}

void MessageVisitor::visit(__attribute__((unused)) ByeMessage& bye) {
  std::cout << "BYE\n";
  client.state = Client::State::END;
}

void MessageVisitor::visit(__attribute__((unused)) JoinMessage& join){};

void MessageVisitor::visit(__attribute__((unused)) ConfirmMessage& confirm){};

void MessageVisitor::visit(__attribute__((unused)) AuthMessage& auth){};

}  // namespace Message
