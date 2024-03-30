#include "Message/ReplyMessage.hpp"

namespace Message {

ReplyMessage::ReplyMessage(bool success, const std::string& content)
    : success(success), content(content) {
  type = Type::REPLY;
}

void ReplyMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ReplyMessage::tcpSerialize() const {
  std::string status = success ? "OK" : "NOK";
  return "REPLY " + status + " IS " + content;
}

std::string ReplyMessage::udpSerialize() const {
  return "";
}

}  // namespace Message
