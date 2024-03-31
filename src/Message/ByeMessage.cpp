#include "Message/ByeMessage.hpp"
#include <vector>
#include "Message/MessageVisitor.hpp"

namespace Message {

ByeMessage::ByeMessage(const uint16_t messageID) {
  id = messageID;
  type = Type::BYE;
}

std::string ByeMessage::tcpSerialize() const {
  return "BYE" + Message::clrf;
}

std::vector<uint8_t> ByeMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::BYE));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));
  return message;
}

void ByeMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

}  // namespace Message
