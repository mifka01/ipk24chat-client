/**
 * @file src/Message/MsgMessage.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <regex>

#include "Message/MessageVisitor.hpp"
#include "Message/MsgMessage.hpp"
#include "utils.hpp"

namespace Message {

MsgMessage::MsgMessage(const uint16_t messageID,
                       const std::string& displayName,
                       const std::string& content)
    : displayName(displayName), content(content) {
  id = messageID;
  type = Type::MSG;

  if (!std::regex_match(displayName, std::regex(Pattern::DISPLAY_NAME))) {
    throw std::invalid_argument("Invalid format of display name");
  }

  if (!std::regex_match(content, std::regex(Pattern::CONTENT))) {
    throw std::invalid_argument("Invalid format of content");
  }
}

void MsgMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string MsgMessage::tcpSerialize() const {
  return "MSG FROM " + displayName + " IS " + content + Message::CLRF;
}

std::vector<uint8_t> MsgMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::MSG));
  uint16_t id = htons(this->id);
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(static_cast<uint8_t>(id));
  addBytes(message, displayName);
  addBytes(message, content);
  return message;
}

}  // namespace Message
