#pragma once
#include <string>
#include "Message.hpp"
#include "MessageVisitor.hpp"

namespace Message {

class ReplyMessage : public Message {
 public:
  bool success;
  std::string content;

  ReplyMessage(const uint16_t messageID,
               bool success,
               const std::string& content);

  void accept(MessageVisitor& visitor) override;

  std::string tcpSerialize() const override;
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
