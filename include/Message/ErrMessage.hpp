#pragma once
#include "Message/Message.hpp"
#include <string>

class ErrMessage : public Message {

public:
  const std::string username;
  const std::string content;

  ErrMessage(const std::string &username, const std::string &content)
      : Message(MessageType::ERR), username(username), content(content) {}
};
