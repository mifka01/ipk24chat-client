#include "Message/MsgMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

MsgMessage::MsgMessage(const std::string& displayName,
                       const std::string& content)
    : displayName(displayName), content(content) {
  type = Type::MSG;
}

void MsgMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string MsgMessage::tcpSerialize() const {
  return "MSG FROM " + displayName + " IS " + content;
}

std::string MsgMessage::udpSerialize() const {
  return "";
}

}  // namespace Message
