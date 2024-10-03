#pragma once
#include "Message/Message.hpp"
#include <string>

class AuthMessage : public Message {

public:
  const std::string username;
  const std::string displayName;
  const std::string secret;

  AuthMessage(const std::string username, const std::string displayName,
              const std::string secret)
      : Message(MessageType::AUTH), username(username),
        displayName(displayName), secret(secret) {}

  AuthMessage(const u_int16_t id, const std::string username,
              const std::string displayName, const std::string secret)
      : Message(MessageType::AUTH, id), username(username),
        displayName(displayName), secret(secret) {}
};
