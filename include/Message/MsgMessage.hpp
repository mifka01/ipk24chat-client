#pragma once
#include "Message/ResponseMessage.hpp"
#include <string>

class MsgMessage : public ResponseMessage {

public:
  const std::string displayName;
  const std::string content;

  MsgMessage(const std::string &displayName, const std::string &content)
      : ResponseMessage(MessageType::MSG), displayName(displayName),
        content(content) {}

  MsgMessage(const u_int16_t id, const std::string &displayName,
             const std::string &content)
      : ResponseMessage(MessageType::MSG, id), displayName(displayName),
        content(content) {}

  std::string toString() const override;
};
