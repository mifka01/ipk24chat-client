#include "Message/AuthMessage.hpp"
#include "Message/MessageVisitor.hpp"

namespace Message {

AuthMessage::AuthMessage(const std::string& username,
                         const std::string& displayName,
                         const std::string& secret)
    : username(username), displayName(displayName), secret(secret) {
  type = Type::AUTH;
}

void AuthMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string AuthMessage::tcpSerialize() const {
  return "AUTH " + username + " AS " + displayName + " USING " + secret;
}
std::string AuthMessage::udpSerialize() const {
  return "";
}

}  // namespace Message
