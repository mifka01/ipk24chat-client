#include "Message/MessageVisitor.hpp"
#include "Client/Client.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "iostream"

namespace Message {

void MessageVisitor::visit(ReplyMessage& reply) {
  if (client.state == Client::State::AUTH ||
      client.state == Client::State::OPEN) {
    if (reply.success) {
      std::cerr << "Success: " << reply.content << "\n";
      client.state = Client::State::OPEN;
    } else {
      client.state = Client::State::START;
      std::cerr << "Failure: " << reply.content << "\n";
    }
  }
}

void MessageVisitor::visit(MsgMessage& msg) {
  std::cout << msg.displayName << ": " << msg.content << "\n";
}

void MessageVisitor::visit(__attribute__((unused)) ByeMessage& bye) {
  std::cout << "BYE\n";
  client.state = Client::State::END;
  exit(0);
}

void MessageVisitor::visit(ErrMessage& err) {
  if (client.state == Client::State::AUTH ||
      client.state == Client::State::OPEN) {
    client.protocol->send(client.protocol->toMessage(Type::BYE, {}));
    client.state = Client::State::END;
  }
  std::cerr << "ERR FROM " << err.displayName << ": " << err.content << "\n";
}

void MessageVisitor::visit(__attribute__((unused)) JoinMessage& join) {}
void MessageVisitor::visit(__attribute__((unused)) AuthMessage& auth) {}
void MessageVisitor::visit(__attribute__((unused)) ConfirmMessage& auth) {}

}  // namespace Message
