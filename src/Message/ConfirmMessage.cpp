/**
 * @file src/Message/ConfirmMessage.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
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

std::string ConfirmMessage::tcpSerialize() const {
  return "";
}

std::vector<uint8_t> ConfirmMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::CONFIRM));
  uint16_t id = htons(this->id);
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(static_cast<uint8_t>(id));
  return message;
}
}  // namespace Message
