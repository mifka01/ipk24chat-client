#include <vector>

#include "Message/ConfirmMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

ConfirmMessage::ConfirmMessage(const uint16_t messageID) {
  id = messageID;
  type = Type::CONFIRM;
}

void ConfirmMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ConfirmMessage::tcpSerialize() const {}

std::vector<uint8_t> ConfirmMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::CONFIRM));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));
  return message;
}
}  // namespace Message
