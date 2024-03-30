#pragma once
#include <string>
#include "Type.hpp"

namespace Message {

class MessageVisitor;

class Message {
 public:
  Type type;

  virtual void accept(MessageVisitor& visitor) = 0;

  virtual std::string tcpSerialize() const = 0;
  virtual std::string udpSerialize() const = 0;

  virtual ~Message() = default;
};

}  // namespace Message
