#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Pattern.hpp"
#include "Type.hpp"

namespace Message {

class MessageVisitor;

class Message {
 public:
  uint16_t id = 0;
  Type type;

  virtual void accept(MessageVisitor& visitor) = 0;

  virtual std::string tcpSerialize() const = 0;
  virtual std::vector<uint8_t> udpSerialize() const = 0;

  virtual ~Message() = default;
};

}  // namespace Message
