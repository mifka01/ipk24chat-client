#pragma once
#include "Message/Message.hpp"
#include <string>

class ResponseMessage : public Message {

public:
  ResponseMessage(MessageType type) : Message(type) {}
  ResponseMessage(MessageType type, const u_int16_t id) : Message(type, id) {}

  virtual std::string toString() const = 0;
};
