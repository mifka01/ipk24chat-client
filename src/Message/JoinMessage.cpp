#include <regex>

#include "Message/JoinMessage.hpp"
#include "Message/MessageVisitor.hpp"
#include "utils.hpp"

namespace Message {

JoinMessage::JoinMessage(const uint16_t messageID,
                         const std::string& channelID,
                         const std::string& displayName)
    : channelID(channelID), displayName(displayName) {
  id = messageID;
  type = Type::JOIN;

  if (!std::regex_match(channelID, std::regex(Pattern::CHANNEL_ID))) {
    throw std::invalid_argument("Invalid format of channel ID");
  }

  if (!std::regex_match(displayName, std::regex(Pattern::DISPLAY_NAME))) {
    throw std::invalid_argument("Invalid format of display name");
  }
}

void JoinMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string JoinMessage::tcpSerialize() const {
  return "JOIN " + channelID + " AS " + displayName + Message::CLRF;
}

std::vector<uint8_t> JoinMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::JOIN));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));
  addBytes(message, channelID);
  addBytes(message, displayName);
  return message;
}
}  // namespace Message
