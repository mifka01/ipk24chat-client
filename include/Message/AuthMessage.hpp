#pragma once
#include <string>
#include "Message.hpp"

namespace Message {

class AuthMessage : public Message {
  struct UDPAuth {
    uint8_t type = 0x02;
    char username[32];
    char displayName[32];
    char secret[32];
  };

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
