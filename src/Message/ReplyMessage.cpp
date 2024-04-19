/**
 * @file src/Message/ReplyMessage.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <regex>

#include "Message/ReplyMessage.hpp"
#include "utils.hpp"

namespace Message {

ReplyMessage::ReplyMessage(const uint16_t messageID,
                           bool success,
                           const std::string& content,
                           const uint16_t refMessageID)
    : success(success), content(content), refMessageID(refMessageID) {
  id = messageID;
  type = Type::REPLY;

  if (!std::regex_match(content, std::regex(Pattern::CONTENT))) {
    throw std::invalid_argument("Invalid format of content");
  }
}

void ReplyMessage::accept(MessageVisitor& visitor) {
  visitor.visit(*this);
}

std::string ReplyMessage::tcpSerialize() const {
  std::string status = success ? "OK" : "NOK";
  return "REPLY " + status + " IS " + content + Message::CLRF;
}

std::vector<uint8_t> ReplyMessage::udpSerialize() const {
  std::vector<uint8_t> message;
  message.push_back(static_cast<uint8_t>(Type::REPLY));
  uint16_t id = htons(this->id);
  message.push_back(static_cast<uint8_t>(id >> 8));
  message.push_back(static_cast<uint8_t>(id));
  message.push_back(success ? 1 : 0);
  uint16_t refid = htons(this->refMessageID);
  message.push_back(static_cast<uint8_t>(refid >> 8));
  message.push_back(static_cast<uint8_t>(refid));
  addBytes(message, content);
  return message;
}

}  // namespace Message
