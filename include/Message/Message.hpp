#pragma once
#include <cstdint>

enum class MessageType {
  CONFIRM = 0x00,
  REPLY = 0x01,
  AUTH = 0x02,
  JOIN = 0x03,
  MSG = 0x04,
  ERR = 0xFE,
  BYE = 0xFF
};

class Message {

public:
  MessageType type;
  const uint16_t id;
  static uint16_t sent;
  static uint16_t received;

  Message(MessageType type) : type(type), id(sent++) {}
  virtual ~Message() = default;
};
