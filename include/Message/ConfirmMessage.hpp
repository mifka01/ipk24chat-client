/**
 * @file include/Message/ConfirmMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Message.hpp"

namespace Message {

/**
 * @class ConfirmMessage
 * @brief Represents the CONFIRM message.
 *
 * The CONFIRM message is used to confirm the receipt of a message.
 */
class ConfirmMessage : public Message {
 public:
  /**
   * @brief Constructs a CONFIRM message.
   * @param messageId The message ID.
   */
  ConfirmMessage(const uint16_t messageId);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  [[maybe_unused]] void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs a CONFIRM message for TCP protocol.
   * @return The serialized CONFIRM message.
   */
  [[maybe_unused]] std::string tcpSerialize() const override;

  /**
   * @brief Constructs a CONFIRM message for UDP protocol.
   * @return The serialized CONFIRM message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
