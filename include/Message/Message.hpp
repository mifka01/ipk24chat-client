/**
 * @file include/Message/Message.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "Pattern.hpp"
#include "Type.hpp"

namespace Message {

// Forward declaration
class MessageVisitor;

/**
 * @class Message
 * @brief Represents a message.
 *
 * The Message class is the base class for all messages.
 */
class Message {
 protected:
  const std::string CLRF = "\r\n";

 public:
  uint16_t id = 0;
  Type type;

  virtual ~Message() = default;

  /**
   * @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  virtual void accept(MessageVisitor& visitor) = 0;

  /**
   * @brief Constructs a message for TCP protocol.
   * @return The serialized message.
   */
  virtual std::string tcpSerialize() const = 0;

  /** @brief Constructs a message for UDP protocol.
   * @return The serialized message.
   */
  virtual std::vector<uint8_t> udpSerialize() const = 0;
};

}  // namespace Message
