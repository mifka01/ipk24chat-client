/**
 * @file src/Message/AuthMessage.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <regex>

#include "Message/AuthMessage.hpp"
#include "Message/MessageVisitor.hpp"
#include "utils.hpp"

namespace Message {

AuthMessage::AuthMessage(const uint16_t messageID,
                         const std::string& username,
                         const std::string& displayName,
                         const std::string& secret)
    : username(username), displayName(displayName), secret(secret) {
  id = messageID;
  type = Type::AUTH;
  if (!std::regex_match(username, std::regex(Pattern::USERNAME))) {
    throw std::invalid_argument("Invalid format of username");
  }
  if (!std::regex_match(displayName, std::regex(Pattern::DISPLAY_NAME))) {
    throw std::invalid_argument("Invalid format of display name");
  }
  if (!std::regex_match(secret, std::regex(Pattern::SECRET))) {
    throw std::invalid_argument("Invalid format of secret");
  }
}

void AuthMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string AuthMessage::tcpSerialize() const {
  return "AUTH " + username + " AS " + displayName + " USING " + secret +
         Message::CLRF;
}

std::vector<uint8_t> AuthMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::AUTH));
  uint16_t id = htons(this->id);
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(static_cast<uint8_t>(id));

  addBytes(message, username);
  addBytes(message, displayName);
  addBytes(message, secret);

  return message;
}

}  // namespace Message
