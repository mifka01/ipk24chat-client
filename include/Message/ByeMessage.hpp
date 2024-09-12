#pragma once
#include "Message/Message.hpp"

class ByeMessage : public Message {

public:
  ByeMessage() : Message(MessageType::BYE) {}
};
