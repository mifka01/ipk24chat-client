#pragma once
#include <string>

#include "Message.hpp"

namespace Message {

class AuthMessage : public Message {
 public:
  std::string username;
  std::string displayName;
  std::string secret;

  AuthMessage(const uint16_t messageID,
              const std::string& username,
              const std::string& displayName,
              const std::string& secret);

  void accept(MessageVisitor& visitor) override;
  std::string tcpSerialize() const override;
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
