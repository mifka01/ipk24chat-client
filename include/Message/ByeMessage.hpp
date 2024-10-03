#pragma once
#include "Message/ResponseMessage.hpp"

class ByeMessage : public ResponseMessage {

public:
  ByeMessage() : ResponseMessage(MessageType::BYE) {}
  ByeMessage(const u_int16_t id) : ResponseMessage(MessageType::BYE, id) {}

  std::string toString() const override;
};
