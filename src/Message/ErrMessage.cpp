#include "Message/ErrMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

ErrMessage::ErrMessage(const std::string& displayName,
                       const std::string& content)
    : displayName(displayName), content(content) {
  type = Type::ERR;
}

void ErrMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ErrMessage::tcpSerialize() const {
  return "ERR FROM " + displayName + " IS " + content;
}

std::string ErrMessage::udpSerialize() const {
  return "";
}
}  // namespace Message
