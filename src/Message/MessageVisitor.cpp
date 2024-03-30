#include "Message/MessageVisitor.hpp"
#include "Client/Client.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "iostream"

namespace Message {

void MessageVisitor::visit(ReplyMessage& reply) {
  Client::State state = client.getState();
  if (state == Client::State::AUTH || state == Client::State::OPEN) {
    if (reply.success) {
      std::cerr << "Success: " << reply.content << "\n";
      client.setState(Client::State::OPEN);
    } else {
      client.setState(Client::State::START);
      std::cerr << "Failure: " << reply.content << "\n";
    }
  }
}

void MessageVisitor::visit(MsgMessage& msg) {
  std::cout << msg.displayName << ": " << msg.content << "\n";
}

void MessageVisitor::visit(__attribute__((unused)) ByeMessage& bye) {
  std::cout << "BYE\n";
  client.setState(Client::State::END);
  exit(0);
}

void MessageVisitor::visit(ErrMessage& err) {
  Client::State state = client.getState();
  if (state == Client::State::AUTH || state == Client::State::OPEN) {
    client.protocol.send(
        client.session.socket,
        client.protocol.toMessage(Type::BYE, {}, client.session));
    client.setState(Client::State::END);
  }
  std::cerr << "ERR FROM " << err.displayName << ": " << err.content << "\n";
}

void MessageVisitor::visit(__attribute__((unused)) JoinMessage& join) {}
void MessageVisitor::visit(__attribute__((unused)) AuthMessage& auth) {}

}  // namespace Message
