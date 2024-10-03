#pragma once
#include "Message/Message.hpp"

class ConfirmMessage : public Message {

public:
  const uint16_t refId;

  ConfirmMessage(uint16_t refId)
      : Message(MessageType::CONFIRM), refId(refId) {}
};
