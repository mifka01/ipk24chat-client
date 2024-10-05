#pragma once
#include <cstdint>
#include <string>

enum class MessageType {
  CONFIRM = 0x00,
  REPLY = 0x01,
  AUTH = 0x02,
  JOIN = 0x03,
  MSG = 0x04,
  ERR = 0xFE,
  BYE = 0xFF
};

struct MessagePattern {
  static constexpr const char *USERNAME = "([a-zA-Z0-9\\-]{1,20})";
  static constexpr const char *SECRET = "([a-zA-Z0-9\\-]{1,128})";
  static constexpr const char *DISPLAY_NAME = "([\\x21-\\x7E]{1,20})";
  static constexpr const char *CONTENT = "([\\x20-\\x7E]{1,1400})";
};

class Message {

public:
  MessageType type;
  const uint16_t id;
  static uint16_t sent;
  static uint16_t received;

  Message(MessageType type, const uint16_t id) : type(type), id(id) {}
  Message(MessageType type) : type(type), id(sent) {}
  virtual ~Message() = default;

  static std::string MessageTypeToString(MessageType type);
  static MessageType StringToMessageType(const std::string &str);
};
