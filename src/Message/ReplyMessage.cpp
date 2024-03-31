#include "Message/ReplyMessage.hpp"
#include <regex>
#include "utils.hpp"

namespace Message {

ReplyMessage::ReplyMessage(const uint16_t messageID,
                           bool success,
                           const std::string& content)
    : success(success), content(content) {
  id = messageID;
  type = Type::REPLY;

  if (!std::regex_match(content, std::regex(Pattern::content))) {
    throw std::invalid_argument("Invalid format of content");
  }
}

void ReplyMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ReplyMessage::tcpSerialize() const {
  std::string status = success ? "OK" : "NOK";
  return "REPLY " + status + " IS " + content;
}

std::vector<uint8_t> ReplyMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::REPLY));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(success ? 1 : 0);
  addBytes(message, content);
  return message;
}

}  // namespace Message
