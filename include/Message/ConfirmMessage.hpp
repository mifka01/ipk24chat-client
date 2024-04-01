#pragma once
#include "Message.hpp"

namespace Message {

class ConfirmMessage : public Message {
 public:
  ConfirmMessage(const uint16_t messageId);

  void accept(MessageVisitor& visitor) override;
  std::string tcpSerialize() const override;
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
