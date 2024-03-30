#pragma once
#include <string>
#include "Message.hpp"

namespace Message {

class JoinMessage : public Message {
 public:
  std::string channelID;
  std::string displayName;

  JoinMessage(const std::string& channelID, const std::string& displayName);

  void accept(MessageVisitor& visitor) override;

  std::string tcpSerialize() const override;
  std::string udpSerialize() const override;
};

}  // namespace Message