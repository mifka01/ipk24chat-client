#pragma once
#include "Message/ResponseMessage.hpp"
#include <string>

class ErrMessage : public ResponseMessage {

public:
  const std::string displayName;
  const std::string content;

  ErrMessage(const std::string &displayName, const std::string &content)
      : ResponseMessage(MessageType::ERR), displayName(displayName),
        content(content) {}

  std::string toString() const override;
};
