/**
 * @file src/Message/ByeMessage.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <vector>

#include "Message/ByeMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

ByeMessage::ByeMessage(const uint16_t messageID) {
  id = messageID;
  type = Type::BYE;
}

std::string ByeMessage::tcpSerialize() const {
  return "BYE" + Message::CLRF;
}

std::vector<uint8_t> ByeMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::BYE));
  uint16_t id = htons(this->id);
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(static_cast<uint8_t>(id));
  return message;
}

void ByeMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

}  // namespace Message
