#include "Message/Message.hpp"
#include "Exception/InvalidMessageException.hpp"
#include <unordered_map>

uint16_t Message::sent = 0;
uint16_t Message::received = 0;

std::string Message::MessageTypeToString(MessageType type) {
  switch (type) {
  case MessageType::CONFIRM:
    return "CONFIRM";
  case MessageType::REPLY:
    return "REPLY";
  case MessageType::AUTH:
    return "AUTH";
  case MessageType::JOIN:
    return "JOIN";
  case MessageType::MSG:
    return "MSG";
  case MessageType::ERR:
    return "ERR";
  case MessageType::BYE:
    return "BYE";
  default:
    throw InvalidMessageException("Unsupported message type for conversion");
  }
}

MessageType Message::StringToMessageType(const std::string &str) {
  static const std::unordered_map<std::string, MessageType> stringToType = {
      {"CONFIRM", MessageType::CONFIRM}, {"REPLY", MessageType::REPLY},
      {"AUTH", MessageType::AUTH},       {"JOIN", MessageType::JOIN},
      {"MSG", MessageType::MSG},         {"ERR", MessageType::ERR},
      {"BYE", MessageType::BYE}};

  auto it = stringToType.find(str);
  if (it != stringToType.end()) {
    return it->second;
  }

  throw InvalidMessageException("Unsupported message type for conversion");
}
