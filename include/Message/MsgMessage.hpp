#pragma once
#include <string>
#include "Message.hpp"

namespace Message {

class MsgMessage : public Message {
 public:
  std::string displayName;
  std::string content;

  MsgMessage(const uint16_t messageID,
             const std::string& displayName,
             const std::string& content);

  void accept(MessageVisitor& visitor) override;

  std::string tcpSerialize() const override;
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
