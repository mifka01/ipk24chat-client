#pragma once
#include "Message/ResponseMessage.hpp"
#include <string>

class ReplyMessage : public ResponseMessage {

public:
  const bool success;
  const std::string content;
  const uint16_t refId;

  ReplyMessage(const bool success, const std::string &content,
               const uint16_t refId)
      : ResponseMessage(MessageType::REPLY), success(success), content(content),
        refId(refId) {}

  ReplyMessage(const u_int16_t id, bool success, const std::string &content,
               const uint16_t refId)
      : ResponseMessage(MessageType::REPLY, id), success(success),
        content(content), refId(refId) {}

  std::string toString() const override;
};
