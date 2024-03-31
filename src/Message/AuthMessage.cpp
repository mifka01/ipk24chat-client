#include "Message/AuthMessage.hpp"
#include <regex>
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
  if (!std::regex_match(username, std::regex(Pattern::username))) {
    throw std::invalid_argument("Invalid format of username");
  }
  if (!std::regex_match(displayName, std::regex(Pattern::displayName))) {
    throw std::invalid_argument("Invalid format of display name");
  }
  if (!std::regex_match(secret, std::regex(Pattern::secret))) {
    throw std::invalid_argument("Invalid format of secret");
  }
}

void AuthMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string AuthMessage::tcpSerialize() const {
  return "AUTH " + username + " AS " + displayName + " USING " + secret +
         Message::clrf;
}
std::vector<uint8_t> AuthMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::AUTH));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));

  addBytes(message, username);
  addBytes(message, displayName);
  addBytes(message, secret);

  return message;
}

}  // namespace Message
