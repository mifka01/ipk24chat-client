#pragma once
#include "Message.hpp"
namespace Message {

class ByeMessage : public Message {
 public:
  ByeMessage(const uint16_t messageID);

  std::string tcpSerialize() const override;
  std::vector<uint8_t> udpSerialize() const override;

  void accept(MessageVisitor& visitor) override;
};

}  // namespace Message
