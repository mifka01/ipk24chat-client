#pragma once
#include "Message/Message.hpp"
#include <string>

class ResponseMessage : public Message {

public:
  ResponseMessage(MessageType type) : Message(type) {}
  virtual std::string toString() const = 0;
};
