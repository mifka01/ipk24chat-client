#pragma once
#include <cstdint>

class Message {

public:
  const uint16_t id;
  static uint16_t sent;
  static uint16_t received;

  Message() : id(sent++) {}
};
