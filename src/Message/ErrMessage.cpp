#include "Message/ErrMessage.hpp"
#include <regex>
#include "Message/MessageVisitor.hpp"
#include "utils.hpp"

namespace Message {

ErrMessage::ErrMessage(const uint16_t messageID,
                       const std::string& displayName,
                       const std::string& content)
    : displayName(displayName), content(content) {
  id = messageID;
  type = Type::ERR;

  if (!std::regex_match(displayName, std::regex(Pattern::displayName))) {
    throw std::invalid_argument("Invalid format of display name");
  }

  if (!std::regex_match(content, std::regex(Pattern::content))) {
    throw std::invalid_argument("Invalid format of content");
  }
}

void ErrMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ErrMessage::tcpSerialize() const {
  return "ERR FROM " + displayName + " IS " + content + Message::clrf;
}

std::vector<uint8_t> ErrMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::ERR));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));
  addBytes(message, displayName);
  addBytes(message, content);
  return message;
}
}  // namespace Message
