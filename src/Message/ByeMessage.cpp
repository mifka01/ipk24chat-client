#include "Message/ByeMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

ByeMessage::ByeMessage() {
  type = Type::BYE;
}

std::string ByeMessage::tcpSerialize() const {
  return "BYE";
}

std::string ByeMessage::udpSerialize() const {
  return "";
}

void ByeMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

}  // namespace Message
