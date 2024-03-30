#pragma once
#include "Message.hpp"

namespace Message {

class ByeMessage : public Message {
 public:
  ByeMessage();

  std::string tcpSerialize() const override;
  std::string udpSerialize() const override;

  void accept(MessageVisitor& visitor) override;
};

}  // namespace Message
