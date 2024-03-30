#pragma once
#include <string>
#include "Message.hpp"

namespace Message {

class ErrMessage : public Message {
 public:
  std::string displayName;
  std::string content;

  ErrMessage(const std::string& displayName, const std::string& content);

  void accept(MessageVisitor& visitor) override;

  std::string tcpSerialize() const override;
  std::string udpSerialize() const override;
};

}  // namespace Message
