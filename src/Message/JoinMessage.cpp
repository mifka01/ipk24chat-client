#include "Message/JoinMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

JoinMessage::JoinMessage(const std::string& channelID,
                         const std::string& displayName)
    : channelID(channelID), displayName(displayName) {
  type = Type::JOIN;
}

void JoinMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string JoinMessage::tcpSerialize() const {
  return "JOIN " + channelID + " AS " + displayName;
}

std::string JoinMessage::udpSerialize() const {
  return "";
}
}  // namespace Message
